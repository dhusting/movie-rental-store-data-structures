// -------------------------- hashTableTest.cpp -------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// ----------------------------------------------------------------------------
// Summary - This file contains the specification for the HashTable class
// Assumptions - None
// ----------------------------------------------------------------------------
#include "hashtable.h"
#include <iostream>

using namespace std;

int main() {
    // Create some sample customers
    Customer customer1{1, "John Doe", "2024-03-01", 0, false, {}};
    Customer customer2{28, "Jane Smith", "2024-03-02", 0, false, {}};
    Customer customer3{35, "Alice Johnson", "2024-03-03", 0, false, {}};

    // Instantiate the HashTable
    HashTable hashTable;

    // Insert customers into the hash table
    hashTable.insert(customer1.ID, customer1);
    hashTable.insert(customer2.ID, customer2);
    hashTable.insert(customer3.ID, customer3);

    hashTable.addTransaction(customer1.ID, "teststring", true);
    hashTable.addTransaction(customer1.ID, "teststring", true);
    hashTable.addTransaction(customer1.ID, "teststring", true);

    // Display hash table contents
    cout << "HashTable contents after insertion:" << endl;
    hashTable.display(10); // Display up to 10 elements for demonstration
    cout << "-----------------------------------" << endl;

    // Get and display a specific customer
    try {
        // Attempt to retrieve customer with ID 2
        Customer* retrievedCustomer = hashTable.get(2);
        cout << "Retrieved Customer: " << retrievedCustomer->name << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
    cout << "-----------------------------------" << endl;

    // Remove a customer from the hash table
    // Attempt to remove customer with ID 2
    bool removed = hashTable.remove(2); 
    if (removed) {
        cout << "Customer removed successfully." << endl;
    } else {
        cout << "Customer not found." << endl;
    }

    // Display hash table contents after removal
    cout << "HashTable contents after removal:" << endl;
    hashTable.display(10); // Display up to 10 elements for demonstration

    return 0;
}