#ifndef MY_HASHMAP_H
#define MY_HASHMAP_H

#include <vector>
#include <list>
#include <utility>

// This is a simple hash map implementation using separate chaining.
// We use a vector of lists, where each list stores key-value pairs that hash to the same bucket.
class MyHashMap {
private:

     // oops private cllass
    // Let's pick a prime number for the number of buckets. This helps reduce the chance of collisions.
    static const int BUCKET_SIZE = 10007;
    
    // Each bucket is a list that holds pairs of (key, value).
    // When multiple keys land in the same bucket (collision), they are stored in this list.
    std::vector<std::list<std::pair<int, int>>> buckets;

    // This is our hash function. 
    // We simply take the key modulo BUCKET_SIZE to decide which bucket it goes into.
    int hash(int key) const {
        return key % BUCKET_SIZE;
    }

public:
    // When we create the hash map, initialize all the buckets.
    MyHashMap() : buckets(BUCKET_SIZE) {}

    // Put a key-value pair into the hash map.
    // If the key already exists, update its value.
    void put(int key, int value) {
        int index = hash(key);
        // Check if the key already exists in the bucket.
        for (auto& entry : buckets[index]) {
            if (entry.first == key) {
                // Key found, just update the value.
                entry.second = value;
                return;
            }
        }
        // Key not found, so add it at the end of the bucket's list.
        buckets[index].emplace_back(key, value);
    }

    // Get the value for a given key.
    // If the key doesn't exist, return -1.
    int get(int key) const {
        int index = hash(key);
        // Look through the bucket for the key.
        for (const auto& entry : buckets[index]) {
            if (entry.first == key) {
                // Found it! Return the value.
                return entry.second;
            }
        }
        // If we get here, the key wasn't in the map.
        return -1;
    }

    // Remove a key-value pair from the map.
    void remove(int key) {
        int index = hash(key);
        // Look through the bucket to find the key.
        for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
            if (it->first == key) {
                // Found the key, erase it from the bucket's list.
                buckets[index].erase(it);
                return;
            }
        }
        // If not found, nothing to do.
    }
};

#endif // MY_HASHMAP_H
