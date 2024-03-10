// -------------------------------hashtable.h ---------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// ----------------------------------------------------------------------------
// Summary - This file contains the specification for the HashTable class
// Assumptions - None
// ----------------------------------------------------------------------------
#include <string>
#include <list>

using namespace std;

struct Transaction {
    int transactionID;
    string borrowDate;
    string nodeID;
    string dueDate;
    string returnDate;
    string transactionDetail;
};

struct Customer {
    int ID;
    string name;
    string dateCreated;
    int infractionCount;
    bool banned;
    list<Transaction> transactions;
};

class HashTable {
    private:
        struct KeyValuePair {
            int customerID;
            Customer customer;
        };

        int hashSize;
        KeyValuePair* hashTable;

        // getHashIndex()
        // Returns index in hash table based on value of key
        // Precondition: NONE
        // Postcondtion: Index returned.
        int getHashIndex(const int key) const {
            return key % hashSize;
        }

    public:
        // --------------------------------------------------------------------
        // Default Constructor
        // Initializes an empty HashTable with size of hashSize
        // Precondition: NONE
        // Postcondition: Initialize an empty HashTable
        HashTable(int size) : hashSize(size){
            hashTable = new KeyValuePair[hashSize];
        };
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
        void insert(const int, const Customer);
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
        bool remove(const int);
        // Pseudocode:
        //  Calculate hash value
        //  Check location of array for the key
        //  Keep moving forward until you find key or reach empty spot
        //  Replace value with empty customer information.reset
        //   - Set ID to -1 to indicate removal. 

        // --------------------------------------------------------------------
        // get()
        // Gets value specified by key
        // Precondition: Key and value should exist
        // Postcondition: Returns value specified by key
        Customer get(const int) const;
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
        void display(const int) const;
        // Pseudocode:
        //  for (length of hash array)
        //   output value, if not empty to cout
};