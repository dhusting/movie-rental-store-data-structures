// -------------------------------hashtable.h ----------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// ----------------------------------------------------------------------------
// Summary - This file contains the implmentation for the HashTable class
// Assumptions - None
// ----------------------------------------------------------------------------
#include <chrono>
#include <functional>
#include <iostream>
#include <iomanip>
#include <list>
#include <sstream>

#include "hashtable.h"

using namespace std;
using namespace std::chrono;

 // Used for calculating due date from borrow date
const uint64_t TWO_WEEKS = 1209600000; //ms

// Return number of seconds since January 1st, 1970
uint64_t HashTable::getCurrentTimestamp() {
    milliseconds ms = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch());

    return ms.count();
}

string HashTable::msTimestampToString(uint64_t milliseconds) {
    // Convert milliseconds to system_clock time_point
    time_point<system_clock> tp = 
        time_point<system_clock>() + chrono::milliseconds(milliseconds);

    // Convert time_point to time_t for conversion to tm struct
    auto timeT = system_clock::to_time_t(tp);

    // Convert to tm struct for formatting
    tm bt = *localtime(&timeT);

    // Use stringstream for formatting
    ostringstream oss;

    oss << put_time(&bt, "%Y%m%d_%H%M%S");
    int milliseconds_part = milliseconds % 1000;
    oss << "." << setw(3) << setfill('0') << milliseconds_part;

    return oss.str();
}

// ----------------------------------------------------------------------------
// insert()
// Inserts value specified by key
// Precondition: None
// Postcondition: Hash Table is updated with key value pair if the entry does 
// not exist.
bool HashTable::insert(const Customer customer) {
    int index = getHashIndex(customer.ID);
    int originalIndex = index;
    bool inserted = false;

    do {
        // If the spot is empty or previously removed (ID = 0 or -1)
        // Insert new customer
        if (hashTable[index].customerID == 0 || hashTable[index].customerID == -1) {
            hashTable[index].customerID = customer.ID;
            hashTable[index].customer = customer;
            inserted = true;
            break;
        }

        // Linear probing: go to the next index
        index = (index + 1) % hashSize;
    } while (index != originalIndex);

    if (!inserted)
        cout << "HashTable is full or no suitable position to insert.\n";

    return inserted;
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
    bool removed = false;

    do {
        if (hashTable[index].customerID == key) {
            hashTable[index].customerID = -1; // Mark as removed
            return true;
        } else if (hashTable[index].customerID == 0) {
            // If we hit an empty slot, the item was never in the table
            return false;
        }

        // Linear probing: go to the next index
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

        // Linear probing: go to the next index
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
    hash<std::string> hasher;
    string uid, borrow, due;
    
    // Add transaction if customer exists
    if (temp != nullptr) {
        if (isBorrow) {
            // If transaction is a borrow, populate transaction data and 
            // push to front of list.
            borrow = msTimestampToString(getCurrentTimestamp());
            due = msTimestampToString(getCurrentTimestamp() + TWO_WEEKS);
            // Generate UID by hashing string of customer ID and borrowed time.
            uid = to_string(hasher(to_string(customerID) + borrow));
            temp->transactions.push_front(
                Transaction{uid, borrow, due, "N/A", details,}
            );
            return true;
        } else {
            // If transaction is a return, search customer transaction log
            // from latest to earliest and update return date and push to front 
            // of list. 
            for (it = temp->transactions.end(); 
                it != temp->transactions.begin(); it--) {
                if (it->transactionDetail == details) {
                    cout << "Transaction found: " << details << endl;
                    // Set return date
                    it->returnDate = msTimestampToString(getCurrentTimestamp());
                    // Swap found transaction to front
                    temp->transactions.splice(temp->transactions.begin(), temp->transactions, it, next(it));
                    return true;
                }
            }
            cout << "Error: transaction not found: " << details << endl;
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
void HashTable::display(const int customerlimit, const int transactionslimit) const {
    Customer* temp;
    list<Transaction> tempTransactions;
    list<Transaction>::iterator it;
    int countOfEntries = 0;

    // Traverse list of customers and print details including transactions
    for (int i = 0; countOfEntries < customerlimit && i < hashSize; i++) {
        if (hashTable[i].customerID > 0) { // Assumes ID > 0 for valid entries
            countOfEntries++;
            temp = &hashTable[i].customer;
            tempTransactions = temp->transactions;
            cout << "[Hash Index " << i << "]\n";
            displayHistory(hashTable[i].customerID, transactionslimit);
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
        tempTransactions = temp->transactions;
        cout << "Customer ID " << temp->ID << ", Name: " << temp->name << endl;
        if (!tempTransactions.empty() && limit > 0) {
            cout << "Size: " << tempTransactions.size() << endl;
            cout
            << right << setw(20) << "Transaction #\t"
            << right << setw(20) << "UID\t"
            << right << setw(20) << "Borrow Date\t" 
            << right << setw(20) << "Due Date\t" 
            << right << setw(20) << "Return Date\t" 
            << left << "Details\t" << endl;
        }
        for (it = tempTransactions.begin();
                it != tempTransactions.end() && countOfTransactions < limit;
                ++it) {
            countOfTransactions++;
            cout
            << right << setw(20) << countOfTransactions << "\t"
            << right << setw(20) << it->transactionID << "\t"
            << right << setw(20) << it->borrowDate << "\t"
            << right << setw(20) << it->dueDate << "\t"
            << right << setw(20) << it->returnDate << "\t"
            << left << it->transactionDetail << endl;
        }
    }
}
