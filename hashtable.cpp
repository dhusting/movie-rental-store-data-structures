// -------------------------------hashtable.h ----------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// ----------------------------------------------------------------------------
// Summary - This file contains the implmentation for the HashTable class
// Assumptions - None
// ----------------------------------------------------------------------------
#include <list>
#include <iostream>

#include "hashtable.h"

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
        /* Debug Messages
        //cout << "Processing key: " << key << " customer: " << customer.ID << endl;
        //cout << "Traversing | current index: " << index << endl;
        //cout << "Traversing | current ID: " << hashTable[index].customerID << endl;
        */
        if (hashTable[index].customerID == 0 || hashTable[index].customerID == -1) {
            hashTable[index].customerID = key;
            hashTable[index].customer = customer;
            inserted = true;
            break;
        }

        // Linear probing: go to the next index
        index = (index + 1) % hashSize;
        cout << "Traversing | current ID+: " << hashTable[index].customerID << endl;
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
    return nullptr;
}

// -----------------------------------------------------------------------------
// addTransaction()
// Transactions are either a borrow or return.
// If transaction is a borrow, creates a new transaction in the HashTable. 
// ID is created off of date customer ID and all other details.
// If transaction is a return, searches for the transaction given the customer
// ID and updates the return date.
// Transaction is moved to front of list to maintain chronological order. 
// Precondition: Customer id, transaction details, and isReturn parameters
// Postcondition: a new transaction transaction is created in the table
// if the customer exists
bool HashTable::addTransaction(int customerID, string details, bool isBorrow) {
    Customer* temp = get(customerID);
    if (temp != nullptr) {
        // If customer exists
        if (isBorrow) {// If the transaction is a borrow, populate transaction data and 
            // push to front of list. 
            temp->transactions.push_front(
                Transaction{
                    "transactionID_holder",
                    "borrowDate_holder",
                    "dueDate_holder",
                    "returnDate_holder",
                    details,
                    }
                );
            return true;
        } else { 
            // If the transaction is a return, search customer transaction log, 
            // update return date and push to front of list. 
            // TODO;
            return true;
        }
    } else
        return false;
}


// ----------------------------------------------------------------------------
// display()
// Outputs hash table to console for debugging
// Precondition: None
// Postcondition: Output of hash table to console
void HashTable::display(const int limit) const {
    Customer* temp;
    list<Transaction> tempTransactions;
    list<Transaction>::iterator it;
    int countOfEntries = 0;

    // Traverse list of customers and print details including transactions
    for (int i = 0; countOfEntries < limit && i < hashSize; ++i) {
        if (hashTable[i].customerID > 0) { // Assumes ID > 0 for valid entries
            countOfEntries++;
            temp = &hashTable[i].customer;
            tempTransactions = temp->transactions;
            cout << "Index " << i << ": ID " << hashTable[i].customerID
                 << ", Name: " << temp->name << endl;
            int count = 0;
            for (it = tempTransactions.begin();
                 it != tempTransactions.end() && count < limit;
                 ++it) {
                count++;
                cout << " - Transaction " << count << ":";
                cout << it->transactionID << " "
                     << it->borrowDate << " "
                     << it->dueDate << " "
                     << it->returnDate << " "
                     << it->transactionDetail << endl;
            }
        }
    }
}