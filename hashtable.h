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
        int arraySize;
         // HashTable Elements
        struct KeyValuePair {
            int key;
            ValueType value;
            KeyValuePair(int k, ValueType v) : key(k), value(v) {}
        };

        KeyValuePair hashTable[];

        // getHashIndex()
        // Returns index in hash table based on value of key
        // Precondition: NONE
        // Postcondtion: Index returned.
        int getHashIndex(const KeyType& key) const {
            std::hash<KeyType> hasher;
            return hasher(key) % hashSize;
        }

    public:
        // --------------------------------------------------------------------
        // Default Constructor
        // Initializes an empty HashTable with size of hashSize
        // Precondition: NONE
        // Postcondition: Initialize an empty HashTable
        HashTable(int hashSize) {this->hashSize = hashSize; hashTable = new KeyValuePair[hashSize]};
        // Pseudocode:
        // Initialize array with hashSize and set to hashTable

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
        // Pseudocode:
        //  getHashIndex from KeyType
        //  Attempt to insert at hashIndex into hashTable
        //  If not sucessful, increment index and try again.
        //  Abort if end of array

        // --------------------------------------------------------------------
        // remove()
        // Removes value specified by key, returns true if found and removed.
        //  False if not found
        // Precondition: None
        // Postcondition: Hash Table is updated with key value pair removed
        bool remove(const KeyType&);
        // Pseudocode:
        //  Calculate hash value
        //  Check location of array for the key
        //  Keep moving forward until you find key or reach empty spot
        //  Replace value with empty customer information.
        //   - Set ID to -1 to indicate removal. 

        // --------------------------------------------------------------------
        // get()
        // Gets value specified by key
        // Precondition: Key and value should exist
        // Postcondition: Returns value specified by key
        ValueType get(const KeyType&) const;
        // Pseudocode:
        //  Calculate hash value
        //  Check location of array for the key
        //  Keep moving forward until you find key or reach empty spot
        //  Reutrn copy of value

        // --------------------------------------------------------------------
        // display()
        // Outputs hash table to console for debugging
        // Precondition: None
        // Postcondition: Output of hash table to console
        void display(const KeyType&) const;
        // Pseudocode:
        //  for (length of hash array)
        //   output value, if not empty to cout
};