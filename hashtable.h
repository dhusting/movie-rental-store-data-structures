// -------------------------------hashtable.h ----------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240313
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the HashTable class
// Assumptions - None
// -----------------------------------------------------------------------------
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <chrono>
#include <list>
#include <string>

#include <limits.h>

using namespace std;

const int DEFAULT_HASH_SIZE = 1000;

struct Transaction
{
    string transactionID;
    string borrowDate;
    string dueDate;
    string returnDate;
    string transactionDetail;
};

struct Customer
{
    int ID = 0;
    string name;
    string dateCreated;
    int infractionCount;
    bool banned;
    list<Transaction> transactions;
};

class HashTable
{
    private:
        struct KeyValuePair
        {
            int customerID = 0;
            Customer customer;
        };

        int hashSize;
        KeyValuePair* hashTable;

        // getHashIndex()
        // Returns index in hash table based on value of key customerID
        // Precondition: NONE
        // Postcondtion: Index returned
        int getHashIndex(const int key) const
        {
            return key % hashSize;
        }

        // ---------------------------------------------------------------------
        // getCurrentTimestamp()
        // Gets current time in milliseconds since epoch January 1st, 1970
        // Precondition: NONE
        // Postcondition: Returns milliseconds since epoch
        uint64_t getCurrentTimestamp();

        // ---------------------------------------------------------------------
        // msTimestampToString()
        // Formats milliseconds since epoch to a string in YYYYMMDD_hhmmss.sss
        // Precondition: NONE
        // Postcondition: Returns human readable string
        string msTimestampToString(uint64_t);

    public:
        // ---------------------------------------------------------------------
        // Default Constructor
        // Initializes an empty HashTable with hasSize of DEFAULT_HASH_SIZE
        // Precondition: NONE
        // Postcondition: Empty HashTable of fixed sized is initialized 
        HashTable() : hashSize(DEFAULT_HASH_SIZE)
        {
            hashTable = new KeyValuePair[hashSize];
        };

        // ---------------------------------------------------------------------
        // Destructor
        // Precondition: NONE
        // Postcondition: Clears hashtable array
        ~HashTable()
        {
            delete[] hashTable;
        };

        // ---------------------------------------------------------------------
        // insert()
        // Inserts value specified by key
        // Precondition: CustomerID in customer should be non-negative
        // Postcondition: Hash Table is updated with key value pair if the 
        // entry does not exist.
        bool insert(const Customer);

        // ---------------------------------------------------------------------
        // remove()
        // Removes value specified by key, returns true if found and removed.
        // False if not found
        // Precondition: None
        // Postcondition: Hash Table is updated with key value pair removed
        bool remove(const int);

        // ---------------------------------------------------------------------
        // get()
        // Gets pointer to customer value specified by key
        // Precondition: Key and value should exist
        // Postcondition: Pointer to value specified by key is returned
        Customer* get(const int) const;

        // ---------------------------------------------------------------------
        // addTransaction()
        // Transactions are either a borrow or return.
        // If transaction is borrow, creates a new transaction in the 
        // HashTable. ID is created off of date customer ID and timestamp
        // If transaction is return, searches transactions given the customerID 
        // and updates the return date. Transaction is then moved to front of 
        // list to maintain chronological order. 
        // Precondition: Customer id, transaction details, and isReturn 
        // parameters
        // Postcondition: a new transaction transaction is created in the table
        // if the customer exists
        bool addTransaction(const int, const string, const bool);

        // ---------------------------------------------------------------------
        // display()
        // Outputs hash table up to specified # of customers and transactions
        // Precondition: None
        // Postcondition: Output of hash table to console
        void display(const int, const int) const;

        // ---------------------------------------------------------------------
        // display()
        // Outputs hash table up to specified # of customers w/o transactions
        // Precondition: None
        // Postcondition: Hash table is output to console
        void display(const int customerEntries) const
        {
            display(customerEntries, 0);
        };

        // ---------------------------------------------------------------------
        // displayHistory()
        // Outputs list of transaction for specified customer w/ specified 
        // number of transactions to display
        // Precondition: None
        // Postcondition: Limited version of hash table is output to console
        void displayHistory(const int, const int) const;

        // ---------------------------------------------------------------------
        // displayHistory()
        // Outputs list of transaction for specified customer w/ max 
        // number of transactions allowable (INT_MAX)
        // Precondition: None
        // Postcondition: Entire hash table of customer is output to console
        void displayHistory(const int customerID) const
        {
            displayHistory(customerID, INT_MAX);
        };
};

#endif