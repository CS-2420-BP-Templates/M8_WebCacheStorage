#include "HashTable.h"

#include <stdexcept>

HashTable::HashTable(int capacity)
    : slots_(capacity) {
    if (capacity == 0) {
        throw std::invalid_argument("HashTable capacity must be greater than zero.");
    }
}

int HashTable::hashFunction(const std::string& url) const {
    // TODO 1:
    // Create a hash value from the characters in key.
    // Return an index between 0 and slots_.size() - 1.
    //
    // Hint: You can add character codes to a size_t sum, then use %.
    // This simple approach is for learning; production hash functions
    // should distribute keys more effectively.
    int total = 0;
    for (char i: url) {
        total += i;
    }
    return total % slots_.size(); // Replace this placeholder.
}

bool HashTable::insert(const std::string& key) {
    // TODO 2:
    // Use open addressing with linear probing.
    //
    // 1. Start at hashFunction(key).
    // 2. Examine at most slots_.size() slots.
    // 3. If the key already exists, update its value and return true.
    // 4. If a slot is empty, store the new key-value pair, increment count_,
    //    and return true.
    // 5. If a slot is occupied by a different key, advance to the next slot.
    // 6. Wrap around to slot 0 when you reach the end.
    // 7. If every slot is examined without finding the key or an empty slot,
    //    return false. Do not loop forever.
    int index = hashFunction(key);
    if (search(key)) return true;
    // Linear probing checks each slot until the key is found
    // or an empty slot is available.
    for (int i = 0; i < slots_.size(); ++i) {
        int currentIndex = (index+i) % slots_.size();

        // Empty slot: insert the new entry.
        if (slots_[currentIndex].empty) {
            slots_[currentIndex] = Bucket{key, false, false};
            count_++;
            return true;
        }

    }

    // Every slot was checked and the table is full.
    return false; // Replace this placeholder.
}

bool HashTable::search(const std::string& url) const {
    // TODO 3:
    // Use the same linear-probing sequence used by insert().
    //
    // Start at hashFunction(key).
    // - If the key is found, return its value.
    // - If an empty slot is reached, the key is not in the table.
    // - If a different key is found, continue probing.
    // - Examine no more than slots_.size() slots.
    // - Wrap around to slot 0 when needed.


        int index = hashFunction(url);

        // Linear probing searches for the key.
        for (int i = 0; i < slots_.size(); ++i) {
            int currentIndex = (index+i) % slots_.size();

            // An empty slot means the key was never inserted
            // farther along this probe sequence.
            if (slots_[currentIndex].empty && slots_[currentIndex].deleted == false) {
                return false;
            }

            if (slots_[currentIndex].url == url && slots_[currentIndex].deleted == false) {

                return true;
            }
        }


    return false;
}

bool HashTable::remove(const std::string& url) {

    int index = hashFunction(url);

    // Linear probing searches for the key.
    for (int i = 0; i < slots_.size(); ++i) {
        int currentIndex = (index+i) % slots_.size();

        // An empty slot means the key was never inserted
        // farther along this probe sequence.
        if (slots_[currentIndex].empty && slots_[currentIndex].deleted == false) {
            return false;
        }

        if (slots_[currentIndex].url == url && slots_[currentIndex].deleted == false) {
            slots_[currentIndex].deleted = true;
            slots_[currentIndex].empty = true;
            count_--;
            return true;
        }
    }


    return false;

}
int HashTable::size() const {
    // TODO 4: Return the number of unique keys stored in the table.
    return count_; // Replace this placeholder.
}

int HashTable::capacity() const {
    return slots_.size();
}
