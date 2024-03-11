// -------------------------------hashtable.h ----------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// ----------------------------------------------------------------------------
// Summary - This file contains the implmentation for the HashTable class
// Assumptions - None
// ----------------------------------------------------------------------------
#include "hashtable.h"
#include <iostream>

using namespace std;

// ----------------------------------------------------------------------------
// Destructor
// Precondition: NONE
// Postcondition: Clears all dynamically allocated memory.
HashTable::~HashTable() {
    delete[] hashTable;
}

// ----------------------------------------------------------------------------
// insert()
// Inserts value specified by key
// Precondition: None
// Postcondition: Hash Table is updated with key value pair if the entry does 
// not exist.
void HashTable::insert(const int key, const Customer customer) {
    int index = getHashIndex(key);
    int originalIndex = index;
    bool inserted = false;

    do {
        // If the spot is empty or previously removed (ID = -1), insert the new
        if (hashTable[index].customerID == 0 || hashTable[index].customerID == -1) {
            hashTable[index].customerID = key;
            hashTable[index].customer = customer;
            inserted = true;
            break;
        }

        // Linear probing: go to the next index
        index = (index + 1) % hashSize;
    } while (index != originalIndex);

    if (!inserted) {
        cout << "HashTable is full or cannot find suitable position to insert." << endl;
    }
}

// ----------------------------------------------------------------------------
// remove()
// Removes value specified by key, returns true if found and removed.
//  False if not found
// Precondition: None
// Postcondition: Hash Table is updated with key value pair removed
bool HashTable::remove(const int key) {
    int index = getHashIndex(key);
    int originalIndex = index;

    do {
        if (hashTable[index].customerID == key) {
            hashTable[index].customerID = -1; // Mark as removed
            // Optionally, clear other fields in the customer record
            return true;
        } else if (hashTable[index].customerID == 0) {
            // If we hit an empty slot, the item was never in the table
            return false;
        }

        index = (index + 1) % hashSize;
    } while (index != originalIndex);

    return false;
}

// ----------------------------------------------------------------------------
// get()
// Gets value specified by key
// Precondition: Key and value should exist
// Postcondition: Returns value specified by key
Customer* HashTable::get(const int key) const {
    int index = getHashIndex(key);
    int originalIndex = index;

    do {
        if (hashTable[index].customerID == key) {
            return &hashTable[index].customer;
        } else if (hashTable[index].customerID == 0) {
            return nullptr;
        }
        index = (index + 1) % hashSize;
    } while (index != originalIndex);
}

// ----------------------------------------------------------------------------
// display()
// Outputs hash table to console for debugging
// Precondition: None
// Postcondition: Output of hash table to console
void HashTable::display(const int limit) const {
    for (int i = 0; i < limit && i < hashSize; ++i) {
        if (hashTable[i].customerID > 0) { // Assumes ID > 0 for valid entries
            cout << "Index " << i << ": ID " << hashTable[i].customerID
                 << ", Name: " << hashTable[i].customer.name << endl;
        }
    }
}
