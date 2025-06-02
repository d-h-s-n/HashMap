#ifndef MY_HASHMAP_H
#define MY_HASHMAP_H

#include <vector>
#include <list>
#include <utility>

class MyHashMap {
private:
    // We choose a prime number for the number of buckets to reduce collisions.
    static const int BUCKET_SIZE = 10007;
    // Each bucket is a list of (key, value) pairs, to handle collisions by separate chaining.
    std::vector<std::list<std::pair<int, int>>> buckets;

    // Hash function: simple modulo operation.
    int hash(int key) const {
        return key % BUCKET_SIZE;
    }

public:
    // Constructor initializes all buckets.
    MyHashMap() : buckets(BUCKET_SIZE) {}

    // Inserts a key-value pair or updates an existing key.
    void put(int key, int value) {
        int index = hash(key);
        // Search the bucket for the key.
        for (auto& entry : buckets[index]) {
            if (entry.first == key) {
                entry.second = value; // Key exists, so update the value.
                return;
            }
        }
        // Key not found; add a new key-value pair.
        buckets[index].emplace_back(key, value);
    }

    // Retrieves the value associated with the key, or returns -1 if not found.
    int get(int key) const {
        int index = hash(key);
        // Search the bucket for the key.
        for (const auto& entry : buckets[index]) {
            if (entry.first == key) {
                return entry.second; // Key found.
            }
        }
        return -1; // Key not found.
    }

    // Removes the key-value pair from the hash map.
    void remove(int key) {
        int index = hash(key);
        // Search the bucket and erase the key-value pair if found.
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->first == key) {
                buckets[index].erase(it);
                return;
            }
        }
    }
};

#endif // MY_HASHMAP_H
