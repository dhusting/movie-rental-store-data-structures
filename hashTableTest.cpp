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

void prettyPrint(string message) {
    cout << "-----------------------------------\n"
         << message << endl
         << "-----------------------------------\n";
}

int main() {
    // Create some sample customers
    prettyPrint("Creating sample customers");
    Customer customer1{1, "John Doe", "2024-03-01", 0, false, {}};
    Customer customer2{28, "Jane Smith", "2024-03-02", 0, false, {}};
    Customer customer3{35, "Alice Johnson", "2024-03-03", 0, false, {}};

    // Instantiate the HashTable
    prettyPrint("Initializing hashtable");
    HashTable hashTable;

    // Insert customers into the hash table
    prettyPrint("Inserting customers into hashtable");
    hashTable.insert(customer1.ID, customer1);
    hashTable.insert(customer2.ID, customer2);
    hashTable.insert(customer3.ID, customer3);

    // Add dummy transactions to customer1
    prettyPrint("Add dummy transactions to customer1");
    hashTable.addTransaction(customer1.ID, "teststring1", true);
    hashTable.addTransaction(customer1.ID, "teststring2", true);
    hashTable.addTransaction(customer1.ID, "teststring3", true);

    
    // Display hash table contents
    prettyPrint("HashTable contents w/ transactions after insertion:");
    hashTable.display(10, 10);

    prettyPrint("Get and display customer with nonexisting customerID = 2");
    // Attempt to retrieve customer with ID 2
    Customer* retrievedCustomer2 = hashTable.get(2);
    if (retrievedCustomer2 != nullptr)
        cout << "Retrieved Customer: " << retrievedCustomer2->name << endl;
    else 
        cout << "Customer could not be retrieved\n";

    // Remove a customer from the hash table
    // Attempt to remove customer with ID 2
    prettyPrint("Attempt to remove customer with nonexisting customerID = 2");
    bool removed = hashTable.remove(2); 
    if (removed)
        cout << "Customer removed successfully.\n";
    else
        cout << "Customer to be removed not found.\n";

    // Display hash table contents after removal
    prettyPrint("HashTable contents after attempted removal:");
    hashTable.display(10);
    
    prettyPrint("Get and display customer with existing customerID = 35");
    // Attempt to retrieve customer with ID 35
    Customer* retrievedCustomer35 = hashTable.get(35);
    if (retrievedCustomer35 != nullptr)
        cout << "Retrieved Customer: " << retrievedCustomer35->name << endl;
    else 
        cout << "Customer could not be retrieved\n";

    // Remove a customer from the hash table
    // Attempt to remove customer with ID 2
    prettyPrint("Attempt to remove customer with existing customerID = 35");
    removed = hashTable.remove(35); 
    if (removed)
        cout << "Customer removed successfully.\n";
    else
        cout << "Customer to be removed not found.\n";;

    // Display hash table contents after removal
    prettyPrint("HashTable contents after customer removal:");
    hashTable.display(10);

    // Add a return transaction
    prettyPrint("Adding return transaction to customer1:");
    hashTable.addTransaction(customer1.ID, "teststring2", false);

    // Display hash table contents after return
    prettyPrint("HashTable contents after return:");
    hashTable.display(10);

    // Display transaction history of customer 1 up to 1000 entries.
    prettyPrint("Customer 1 transactions:");
    hashTable.displayHistory(customer1.ID, 1000);
    
    return 0;
}