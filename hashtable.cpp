// ---------------------------------product.h ---------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// ----------------------------------------------------------------------------
// Summary - This file contains the implementation for the HashTable class
// Assumptions - None
// ----------------------------------------------------------------------------
#include <string>
#include <list>
#include "hashtable.h"

using namespace std;

// --------------------------------------------------------------------
// Default Constructor
// Initializes an empty HashTable with size of hashSize
// Precondition: NONE
// Postcondition: Initialize an empty HashTable
template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(int _hashSize) {
    // Constructor implementation
    hashSize = _hashSize;
    hashTable = new KeyValuePair[hashSize];
}

// --------------------------------------------------------------------
// Destructor
// Precondition: NONE
// Postcondition: Clears all dynamically allocated memory.
template<typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
    // Destructor implementation
}

// --------------------------------------------------------------------
// insert()
// Inserts value specified by key
// Precondition: None
// Postcondition: Hash Table is updated with key value pair if the 
// entry does not exist.
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType&, const ValueType&) {
    
}

// --------------------------------------------------------------------
// remove()
// Removes value specified by key, returns true if found and removed.
//  False if not found
// Precondition: None
// Postcondition: Hash Table is updated with key value pair removed
template<typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::remove(const KeyType&){
    
}

// --------------------------------------------------------------------
// get()
// Gets value specified by key
// Precondition: Key and value should exist
// Postcondition: Returns value specified by key
template<typename KeyType, typename ValueType>
ValueType HashTable<KeyType, ValueType>::get(const KeyType&) const {

}

// --------------------------------------------------------------------
// display()
// Outputs hash table to console for debugging
// Precondition: None
// Postcondition: Output of hash table to console
template<typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::display(const KeyType&) const {

}