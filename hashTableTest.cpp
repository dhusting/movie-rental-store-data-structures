// -------------------------- hashTableTest.cpp -------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// ----------------------------------------------------------------------------
// Summary - This file contains the specification for the HashTable class
// Assumptions - None
// ----------------------------------------------------------------------------
#include <iostream>
#include <chrono>
#include <thread>

#include "hashtable.h"

using namespace std;

void prettyPrint(string message) {
    cout << "-----------------------------------\n"
         << message << endl
         << "-----------------------------------\n";
}

int main() {
    // Create some sample customers
    cout << "Creating sample customers\n";
    Customer customer1{9999, "John Doe", "2024-03-01", 0, false, {}};
    Customer customer2{1202, "Jane Smith", "2024-03-02", 0, false, {}};
    Customer customer3{4503, "Alice Johnson", "2024-03-03", 0, false, {}};

    // Instantiate the HashTable
    cout << "Initializing hashtable\n";
    HashTable hashTable;

    // Insert customers into the hash table
    prettyPrint("TEST: Inserting customers into hashtable");
    hashTable.insert(customer1);
    hashTable.insert(customer2);
    hashTable.insert(customer3);

    // Display hash table contents
    cout << "HashTable contents w/ new customers, no transactions posted\n";
    hashTable.display(10, 10);

    // Add dummy transactions to customer1
    prettyPrint("TEST: Add dummy transactions to customer1");
    for (int i = 1; i <= 100; i++) {
        hashTable.addTransaction(customer1.ID, "movie", true);
        // Adding ~millisecond delay for unique borrow datetimes
        this_thread::sleep_for(chrono::milliseconds(1));
    }

    // Display hash table contents
    cout << "HashTable contents w/ transactions after insertion\n";
    hashTable.display(10, 10);

    // Add a return transaction
    prettyPrint("TEST: Adding return transaction to customer1:");
    hashTable.addTransaction(customer1.ID, "movie", false);

    // Display hash table contents after return
    cout << "HashTable contents after return:\n";
    hashTable.display(10, 10);

    // Add a return transaction
    prettyPrint("TEST: Adding non-existing return transaction to customer1:");
    hashTable.addTransaction(customer1.ID, "movie34", false);

    prettyPrint("TEST: Get and display customer w/ customerID = 2");
    // Attempt to retrieve customer with ID 2
    Customer* retrievedCustomer2 = hashTable.get(2);
    if (retrievedCustomer2 != nullptr)
        cout << "RESULT: Retrieved Customer: " << retrievedCustomer2->name << endl;
    else 
        cout << "RESULT: Customer could not be retrieved\n";

    // Remove a customer from the hash table
    // Attempt to remove customer with ID 2
    prettyPrint("TEST: Attempt to remove customer w/ customerID = 2");
    bool removed = hashTable.remove(2); 
    if (removed)
        cout << "RESULT: Customer removed successfully.\n";
    else
        cout << "RESULT: Customer to be removed not found.\n";

    // Display hash table contents after removal
    prettyPrint("HashTable contents after attempted removal:");
    hashTable.display(10);
    
    prettyPrint("TEST: Get and display customer w/ customerID = 1202");
    // Attempt to retrieve customer with ID 1202
    Customer* retrievedCustomer35 = hashTable.get(1202);
    if (retrievedCustomer35 != nullptr)
        cout << "RESULT: Retrieved Customer: " << retrievedCustomer35->name << endl;
    else 
        cout << "RESULT: Customer could not be retrieved\n";

    // Remove a customer from the hash table
    // Attempt to remove customer with ID 1202
    prettyPrint("TEST: Attempt to remove customer w/ customerID = 1202");
    removed = hashTable.remove(1202); 
    if (removed)
        cout << "RESULT: Customer removed successfully.\n";
    else
        cout << "RESULT: Customer to be removed not found.\n";;

    // Display hash table contents after removal
    cout << "HashTable contents after customer removal:\n";
    hashTable.display(10);

    // Display transaction history of customer 1 up to 1000 entries.
    prettyPrint("TEST: Customer 1 transactions");
    hashTable.displayHistory(customer1.ID);

    // Add duplicate customerID
    prettyPrint("TEST: Add duplicate customerID = 9999");
    if (!hashTable.insert(Customer{9999, "John Smith(9999)", "2024-03-03", 0, false, {}})) {
        cout << "RESULT: Unsuccessful in added customerID 9999.\n";
    }


    // Add 9996 more customers
    prettyPrint("TEST: Add 999 more customers");
    for (int i = 1; i <= 999; i++) {
        if (!hashTable.insert(Customer{i, "John Smith(" + to_string(i) + ")", "2024-03-03", 0, false, {}})) {
            cout << "RESULT: Customer list exceeded max customers of 1000.\n";
            break;
        }            
    }

    return 0;
}