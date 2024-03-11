// -------------------------------hashtable.h ----------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// ----------------------------------------------------------------------------
// Summary - This file contains the implmentation for the HashTable class
// Assumptions - None
// ----------------------------------------------------------------------------
#include <chrono>
#include <iostream>
#include <sstream>
#include <list>

#include "hashtable.h"

using namespace std;

const uint64_t TWO_WEEKS = 1209600000;

// ----------------------------------------------------------------------------
// Destructor
// Precondition: NONE
// Postcondition: Clears all dynamically allocated memory.
HashTable::~HashTable() {
    delete[] hashTable;
}

// Return number of seconds since January 1st, 1970
uint64_t HashTable::getCurrentTimestamp() {
    chrono::milliseconds ms = chrono::duration_cast< chrono::milliseconds >(
    chrono::system_clock::now().time_since_epoch());

    return ms.count();
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
bool HashTable::addTransaction(
    const int customerID, const string details, const bool isBorrow) {
    Customer* temp = get(customerID);
    list<Transaction>::iterator it;

    if (temp != nullptr) {
        // If customer exists
        if (isBorrow) {// If the transaction is a borrow, populate transaction data and 
            // push to front of list. 
            temp->transactions.push_front(
                Transaction{
                    to_string(customerID),
                    to_string(getCurrentTimestamp()),
                    to_string(getCurrentTimestamp() + TWO_WEEKS),
                    "N/A",
                    details,
                    }
                );
            return true;
        } else {
            for (it = temp->transactions.begin();it != temp->transactions.end(); it++) {
                cout << "Current Transaction: " << it->transactionDetail << endl;
                if (it->transactionDetail == details) {
                    cout << "Transaction found: " << details << endl;
                    // Swap found transaction to front
                    it->returnDate = to_string(getCurrentTimestamp());
                    temp->transactions.splice(temp->transactions.begin(), temp->transactions, it, next(it));
                    return true;
                }
            // If the transaction is a return, search customer transaction log, 
            // update return date and push to front of list. 
            // TODO;
            }
            cout << "Error, transaction not found: " << details << endl;
            return false;
        }
    }
    cout << "Error, customer not found: " << details << endl;
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
    for (int i = 0; countOfEntries < limit && i < hashSize; i++) {
        if (hashTable[i].customerID > 0) { // Assumes ID > 0 for valid entries
            countOfEntries++;
            temp = &hashTable[i].customer;
            tempTransactions = temp->transactions;
            cout << "Hash Index " << i << ": "
                 << "Customer ID " << hashTable[i].customerID << ", "
                 << "Name: " << temp->name << endl;
            displayHistory(hashTable[i].customerID, limit);
        }
    }
}

// ----------------------------------------------------------------------------
// displayHistory()
// Outputs hash table to console for debugging
// Precondition: None
// Postcondition: Output of hash table to console
void HashTable::displayHistory(const int customerID, const int limit) const {
    Customer* temp = get(customerID);
    list<Transaction> tempTransactions;
    list<Transaction>::iterator it;
    int countOfTransactions = 0;

    if (temp != nullptr) {
        cout << "Displaying History\n";
        tempTransactions = temp->transactions;
        cout << "Customer ID " << temp->ID
                << ", Name: " << temp->name << endl;
        for (it = tempTransactions.begin();
                it != tempTransactions.end() && countOfTransactions < limit;
                ++it) {
            countOfTransactions++;
            cout << " - Transaction " << countOfTransactions << ":";
            cout << "ID:" << it->transactionID << " "
                    << "Borrow Date: " << it->borrowDate << " "
                    << "Due Date: " << it->dueDate << " "
                    << "Return Date: " << it->returnDate << " "
                    << "Details: " << it->transactionDetail << endl;
        }
    }
}