// ---------------------------------product.h ------------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the HashTable class
// Assumptions - None
// -----------------------------------------------------------------------------
#include <string>
#include <list>

using namespace std;

template<typename KeyType, typename ValueType>
class HashTable {
    private:
        int hashSize;
         // HashTable Elements
        struct KeyValuePair {
            int key;
            ValueType value;
            KeyValuePair(int k, ValueType v) : key(k), value(v) {}
        };

        // getBucketIndex()
        // Returns index in hash table based on value of key
        // Precondition: NONE
        // Postcondtion: Index returned.
        int getBucketIndex(const KeyType& key) const {
            std::hash<KeyType> hasher;
            return hasher(key) % hashSize;
        }

    public:
        // --------------------------------------------------------------------
        // Default Constructor
        // Initializes an empty HashTable with 
        // Precondition: NONE
        // Postcondition: Initialize an empty HashTable
        HashTable(int hashSize) {this->hashSize = hashSize};

        // --------------------------------------------------------------------
        // Destructor
        // Precondition: NONE
        // Postcondition: Clears all dynamically allocated memory.
        ~HashTable();

        // --------------------------------------------------------------------
        // insert()
        // Inserts value specified by key
        // Precondition: None
        // Postcondition: Hash Table is updated with key value pair if the 
        // entry does not exist.
        void insert(const KeyType&, const ValueType&);

        // --------------------------------------------------------------------
        // remove()
        // Removes value specified by key, returns true if found and removed.
        //  False if not found
        // Precondition: None
        // Postcondition: Hash Table is updated with key value pair removed
        bool remove(const KeyType&);

        // --------------------------------------------------------------------
        // get()
        // Gets value specified by key
        // Precondition: Key and value should exist
        // Postcondition: Returns value specified by key
        ValueType get(const KeyType&) const;

        // --------------------------------------------------------------------
        // display()
        // Outputs hash table to console for debugging
        // Precondition: None
        // Postcondition: Output of hash table to console
        void display(const KeyType&) const;
};