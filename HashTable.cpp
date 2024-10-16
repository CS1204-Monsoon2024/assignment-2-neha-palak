#include <vector>
#include <iostream>
using namespace std;

class HashTable {
private:
    vector<int> keys;
    vector<int> values;
    vector<bool> occupied;
    int capacity;
    int numElements;

    int hash(int key) {
        return key % capacity;
    }

    void resize() {
        int oldCapacity = capacity;
        capacity *= 2; // Double the size
        vector<int> oldKeys = keys;
        vector<int> oldValues = values;
        keys.resize(capacity);
        values.resize(capacity);
        fill(occupied.begin(), occupied.end(), false);
        numElements = 0;
        for (int i = 0; i < oldCapacity; i++) {
            if (occupied[i]) {
                insert(oldKeys[i], oldValues[i]);
            }
        }
    }

public:
    HashTable(int initialSize) : capacity(initialSize), numElements(0) {
        keys.resize(capacity);
        values.resize(capacity);
        occupied.resize(capacity, false);
    }

    void insert(int key, int value) {
        if (float(numElements) / capacity >= 0.8) {
            resize();
        }
        int index = hash(key);
        int i = 0;
        while (occupied[index]) {
            index = (hash(key) + i * i) % capacity;
            i++;
        }
        keys[index] = key;
        values[index] = value;
        occupied[index] = true;
        numElements++;
    }

    int search(int key) {
        int index = hash(key);
        int i = 0;
        while (occupied[index]) {
            if (keys[index] == key) {
                return values[index];
            }
            index = (hash(key) + i * i) % capacity;
            i++;
        }
        return -1; // Key not found
    }

    void remove(int key) {
        int index = hash(key);
        int i = 0;
        while (occupied[index]) {
            if (keys[index] == key) {
                occupied[index] = false;
                numElements--;
                return;
            }
            index = (hash(key) + i * i) % capacity;
            i++;
        }
    }
};

int main() {
    HashTable ht(10);
    ht.insert(1, 100);
    ht.insert(2, 200);
    cout << "Search for key 1: " << ht.search(1) << endl;
    ht.remove(1);
    cout << "Search for key 1 after deletion: " << ht.search(1) << endl;
    return 0;
}