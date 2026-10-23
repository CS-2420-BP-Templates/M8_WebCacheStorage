#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <utility>
#include <vector>

struct Bucket {
    std::string url;
    bool empty = true;
    bool deleted = false;
};


class HashTable {
public:
    explicit HashTable(int capacity = 23);

    // Inserts a new key-value pair or updates the value for an existing key.
    // Returns true if the operation succeeds; false if the table is full.
    bool insert(const std::string& url);

    bool remove(const std::string& url);

    // Returns the value associated with key, or std::nullopt if not found.
    bool search(const std::string& url) const;

    int size() const;
    int capacity() const;

private:

    std::vector<Bucket> slots_;
    int count_ = 0;

    // TODO 1: Implement a hash function that returns a valid slot index.
    int hashFunction(const std::string& url) const;
};
