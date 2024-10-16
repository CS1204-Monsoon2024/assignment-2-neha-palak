#include <vector>
#include <cmath>
#include <iostream>

class HashTable {
private:
    std::vector<int> table;  // The storage for the hash table
    int size;                // Current size of the hash table
    int count;               // Count of elements in the hash table
    double loadFactorThreshold;  // Load factor threshold for resizing

    // Hash function to compute the index
    int hash(int key) const {
        return key % size;
    }

    // Helper function to find the next prime number greater than or equal to `n`
    int nextPrime(int n) const {
        while (true) {
            bool isPrime = true;
            for (int i = 2; i <= std::sqrt(n); i++) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return n; // Return if prime
            n++; // Check next number
        }
    }

    // Function to resize and rehash the hash table
    void resize() {
        int newSize = nextPrime(size * 2);
        std::vector<int> newTable(newSize, -1); // Create new table
        
        for (int i = 0; i < size; i++) {
            if (table[i] != -1 && table[i] != -2) { // -2 indicates a deleted slot
                int key = table[i];
                int index = key % newSize;
                int j = 0;
                while (newTable[(index + j * j) % newSize] != -1) {
                    j++;
                }
                newTable[(index + j * j) % newSize] = key; // Insert into new table
            }
        }
        table = newTable; // Update table to new table
        size = newSize;   // Update size
    }

public:
    // Constructor
    HashTable(int initSize = 5) {
        size = nextPrime(initSize); // Set size to next prime
        table.resize(size, -1);     // Initialize table with -1
        count = 0;                   // Initialize count
        loadFactorThreshold = 0.8;   // Set load factor threshold
    }

    // Insert a key into the hash table
    void insert(int key) {
        if (count >= loadFactorThreshold * size) {
            resize(); // Resize if load factor exceeded
        }
        int index = hash(key);
        int j = 0;

        while (j < size) {
            int probeIndex = (index + (j * j)) % size;
            if (table[probeIndex] == key) {
                std::cout << "Duplicate key insertion is not allowed\n";
                return; // Duplicate found
            }
            if (table[probeIndex] == -1 || table[probeIndex] == -2) {
                table[probeIndex] = key; // Insert key
                count++;
                return; // Key inserted
            }
            j++;
        }
        std::cout << "Max probing limit reached!\n";
    }

    // Remove a key from the hash table
    void remove(int key) {
        int index = hash(key);
        int j = 0;

        while (j < size) {
            int probeIndex = (index + (j * j)) % size;
            if (table[probeIndex] == key) {
                table[probeIndex] = -2; // Mark as deleted
                count--;
                return; // Key removed
            } else if (table[probeIndex] == -1) {
                std::cout << "Element not found\n";
                return; // Element not found
            }
            j++;
        }
        std::cout << "Element not found\n";
    }

    // Search for a key in the hash table
    int search(int key) const {
        int index = hash(key);
        int j = 0;

        while (j < size) {
            int probeIndex = (index + (j * j)) % size;
            if (table[probeIndex] == key) {
                return probeIndex; // Return found index
            } else if (table[probeIndex] == -1) {
                return -1; // Not found
            }
            j++;
        }
        return -1; // Not found
    }

    // Print the contents of the hash table
    void printTable() const {
        for (int i = 0; i < size; i++) {
            if (table[i] == -1) {
                std::cout << "- "; // Empty slot
            } else if (table[i] == -2) {
                std::cout << "- "; // Deleted slot
            } else {
                std::cout << table[i] << " "; // Print key
            }
        }
        std::cout << "\n";
    }
};