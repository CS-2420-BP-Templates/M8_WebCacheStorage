#include <sstream>

#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../externals/catch2/catch.hpp"


#include "../HashTable.h"

using namespace std;



#include "HashTable.h"

#include <stdexcept>

// ---------------------------------------------------------
// Test 1: Constructor and initial state
// ---------------------------------------------------------
TEST_CASE("HashTable initializes correctly", "[hashtable]") {
    HashTable table(10);

    REQUIRE(table.capacity() == 10);
    REQUIRE(table.size() == 0);
}

// ---------------------------------------------------------
// Test 2: Invalid capacity
// ---------------------------------------------------------
TEST_CASE("HashTable rejects zero capacity", "[hashtable]") {
    REQUIRE_THROWS_AS(HashTable(0), std::invalid_argument);
}

// ---------------------------------------------------------
// Test 3: Insert and search
// ---------------------------------------------------------
TEST_CASE("HashTable inserts and searches for URLs", "[hashtable]") {
    HashTable table(10);

    REQUIRE(table.insert("https://www.google.com"));
    REQUIRE(table.size() == 1);

    REQUIRE(table.search("https://www.google.com"));
    REQUIRE_FALSE(table.search("https://www.youtube.com"));
}

// ---------------------------------------------------------
// Test 4: Multiple insertions
// ---------------------------------------------------------
TEST_CASE("HashTable stores multiple URLs", "[hashtable]") {
    HashTable table(10);

    REQUIRE(table.insert("https://www.google.com"));
    REQUIRE(table.insert("https://www.youtube.com"));
    REQUIRE(table.insert("https://www.github.com"));

    REQUIRE(table.size() == 3);

    REQUIRE(table.search("https://www.google.com"));
    REQUIRE(table.search("https://www.youtube.com"));
    REQUIRE(table.search("https://www.github.com"));
}

// ---------------------------------------------------------
// Test 5: Collisions and linear probing
// ---------------------------------------------------------
TEST_CASE("HashTable handles collisions", "[hashtable]") {
    HashTable table(5);

    // The hash function adds character codes.
    // "ab" and "ba" have the same hash.
    REQUIRE(table.insert("ab"));
    REQUIRE(table.insert("ba"));

    REQUIRE(table.size() == 2);
    REQUIRE(table.search("ab"));
    REQUIRE(table.search("ba"));
}

// ---------------------------------------------------------
// Test 6: Wraparound at the end of the table
// ---------------------------------------------------------
TEST_CASE("HashTable wraps around during linear probing", "[hashtable]") {
    HashTable table(5);

    // 'c' and 'h' both hash to index 4 with capacity 5.
    // The second insertion must wrap around to index 0.
    REQUIRE(table.insert("c"));
    REQUIRE(table.insert("h"));

    REQUIRE(table.size() == 2);
    REQUIRE(table.search("c"));
    REQUIRE(table.search("h"));
}

// ---------------------------------------------------------
// Test 7: Duplicate insertion
// ---------------------------------------------------------
TEST_CASE("HashTable does not store duplicate URLs", "[hashtable]") {
    HashTable table(5);

    REQUIRE(table.insert("https://www.google.com"));
    REQUIRE(table.insert("https://www.google.com"));

    REQUIRE(table.size() == 1);
    REQUIRE(table.search("https://www.google.com"));
}

// ---------------------------------------------------------
// Test 8: Remove an existing URL
// ---------------------------------------------------------
TEST_CASE("HashTable removes an existing URL", "[hashtable]") {
    HashTable table(10);

    REQUIRE(table.insert("https://www.google.com"));
    REQUIRE(table.size() == 1);

    REQUIRE(table.remove("https://www.google.com"));

    REQUIRE_FALSE(table.search("https://www.google.com"));
    REQUIRE(table.size() == 0);
}

// ---------------------------------------------------------
// Test 9: Remove a URL that does not exist
// ---------------------------------------------------------
TEST_CASE("HashTable handles removal of missing URLs", "[hashtable]") {
    HashTable table(10);

    REQUIRE(table.insert("https://www.google.com"));

    REQUIRE_FALSE(table.remove("https://www.youtube.com"));

    REQUIRE(table.size() == 1);
    REQUIRE(table.search("https://www.google.com"));
}

// ---------------------------------------------------------
// Test 10: Search beyond a deleted bucket
// ---------------------------------------------------------
TEST_CASE("HashTable searches past deleted buckets", "[hashtable]") {
    HashTable table(5);

    // These URLs collide and occupy consecutive probe positions.
    REQUIRE(table.insert("ab"));
    REQUIRE(table.insert("ba"));

    // Delete the first URL.
    REQUIRE(table.remove("ab"));

    // Searching for the second URL must continue past the
    // deleted bucket.
    REQUIRE(table.search("ba"));

    REQUIRE_FALSE(table.search("ab"));
    REQUIRE(table.size() == 1);
}

// ---------------------------------------------------------
// Test 11: Reuse a deleted bucket
// ---------------------------------------------------------
TEST_CASE("HashTable reuses deleted buckets", "[hashtable]") {
    HashTable table(5);

    REQUIRE(table.insert("ab"));
    REQUIRE(table.insert("ba"));

    REQUIRE(table.remove("ab"));
    REQUIRE(table.size() == 1);

    REQUIRE(table.insert("cd"));
    REQUIRE(table.size() == 2);

    REQUIRE(table.search("ba"));
    REQUIRE(table.search("cd"));
}

// ---------------------------------------------------------
// Test 12: Do not create duplicates beyond a tombstone
// ---------------------------------------------------------
TEST_CASE("HashTable checks for duplicates beyond deleted buckets",
          "[hashtable]") {
    HashTable table(5);

    REQUIRE(table.insert("ab"));
    REQUIRE(table.insert("ba"));

    REQUIRE(table.remove("ab"));

    // "ba" already exists beyond the deleted bucket.
    // Insertion must not create a duplicate in the tombstone.
    REQUIRE(table.insert("ba"));

    REQUIRE(table.size() == 1);
    REQUIRE(table.search("ba"));
}

// ---------------------------------------------------------
// Test 13: Fill the table
// ---------------------------------------------------------
TEST_CASE("HashTable handles a full table", "[hashtable]") {
    HashTable table(3);

    REQUIRE(table.insert("a"));
    REQUIRE(table.insert("b"));
    REQUIRE(table.insert("c"));

    REQUIRE(table.size() == 3);

    // Insertion should fail when every bucket is occupied.
    REQUIRE_FALSE(table.insert("d"));

    REQUIRE(table.size() == 3);

    REQUIRE(table.search("a"));
    REQUIRE(table.search("b"));
    REQUIRE(table.search("c"));
}

// ---------------------------------------------------------
// Test 14: Reuse a bucket after the table becomes full
// ---------------------------------------------------------
TEST_CASE("HashTable can insert after removing from a full table",
          "[hashtable]") {
    HashTable table(3);

    REQUIRE(table.insert("a"));
    REQUIRE(table.insert("b"));
    REQUIRE(table.insert("c"));

    REQUIRE_FALSE(table.insert("d"));

    REQUIRE(table.remove("b"));
    REQUIRE(table.size() == 2);
table.insert("d");
    REQUIRE(table.insert("d"));
    REQUIRE(table.size() == 3);

    REQUIRE(table.search("a"));
    REQUIRE(table.search("c"));
    REQUIRE(table.search("d"));
    REQUIRE_FALSE(table.search("b"));
}

// ---------------------------------------------------------
// Test 15: Removing the same URL twice
// ---------------------------------------------------------
TEST_CASE("HashTable cannot remove the same URL twice",
          "[hashtable]") {
    HashTable table(5);

    REQUIRE(table.insert("ab"));

    REQUIRE(table.remove("ab"));
    REQUIRE_FALSE(table.remove("ab"));

    REQUIRE(table.size() == 0);
    REQUIRE_FALSE(table.search("ab"));
}