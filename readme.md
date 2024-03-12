# [CSS 502] Assignment 4 Rent-a-Reel
## Overview
The core of this project revolves around the Inventory class. The Inventory Class maintains Transactions, Customers, and the inventory of Product - Media (DVDs, VHS, Bluray, etc) of which is categorized by Genres (Comedy, Drama, Classic, etc..) with sub types of Music, Movies, etc..
The inventory can be initialized three ways:
1. Default constructor will create an empty inventory with No name and No address associated.
2. Name and Address constructor will initialize Inventory from backup files. If backup files do not exist an empty Inventory with the specified Name and Address will be created.
3. Command File constructor will initialize an inventory from three files:
    a. data4movies.txt - From this file the movies inventory will be created
    b. data4customers.txt - From this file the customer table will be created
    c. data4commands.txt - From this file commands such as Borrow, Return, etc. Can be executed

## Design Philosophy
- One object to rule them all
    - Only need Inventory class to create an inventory
- Flexibility in building an entity
    - 3 methods of inputting into an inventory
        - File
        - Command
        - API
- Scaling to handle variation and customization
- Backing up

## The Concept
- Prompt was built for polymorphism
    - Genre -> Action, Comedy, etc
- Problems with that implementation
    - Not Scalable, too many classes
    - Different Stores, Different Sort Methods?
- Lowering the skill gap for input
    - Not a programmer, no problem! 
- Expanding market potential
    - Different Products (Hardware, video games, etc)
    - Renting or Buying (Food, hardware, etc)
## Application Flow
1. Create an Inventory object
2. Create a product (abstract)
    - Media implementation already provided. (Can be extended to any product)
    - Media can be DVDs, VHS, Bluray, etc
3. Create a genre for that product
    - Give it a name, a way to parse, and a way to sort
4. Create a movie for that genre
    - Give it a product, a genre, and all the details 

## *HashTable*
The hashtable is based on the closed hashing concept. 
It uses an array of keyvaluepair structs with customerID as the key and customer as a value.

### How to use
#### Initialize HashTable
```
// Instantiate the HashTable
HashTable hashTable;
```

#### Initialize Customers to insert into HashTable
```
// Create some sample customers
Customer customer1{1, "John Doe", "2024-03-01", 0, false, {}};
Customer customer2{2, "Jane Smith", "2024-03-02", 0, false, {}};
Customer customer3{3, "Alice Johnson", "2024-03-03", 0, false, {}};
```

#### Insert Customers into HashTable
```
// Insert customers into the hash table
hashTable.insert(customer1);
hashTable.insert(customer2);
hashTable.insert(customer3);
```

#### To Add Transactions into Customer
```
// Add a borrow transaction
hashTable.addTransaction(customer1.ID, "movie34", true);
// Add a return transaction
hashTable.addTransaction(customer1.ID, "movie34", false);
```

#### To Retrieve Customers from HashTable
```
Customer* retrievedCustomer = hashTable.get(2);
cout << "Retrieved Customer: " << retrievedCustomer->name << endl;
```

#### To Remove Customers from HashTable
```
bool removed = hashTable.remove(2); 
if (removed)
    cout << "Customer removed successfully." << endl;
else
    cout << "Customer not found." << endl;
```

#### To Display HashTable (Customers and/or Transactions in tabular form)
```
// Display hash table contents
cout << "HashTable contents:" << endl;
hashTable.display(10, 20); // Display up to 10 customers and 20 transactions
cout << "-----------------------------------" << endl;
cout << "HashTable contents:" << endl;
hashTable.display(10); // Display up to 10 customers and INT_MAX transactions
cout << "-----------------------------------" << endl;
```

### To test the hashtable class functionality.
`hashtabletest.cpp` contains driver code to test the hashtable functionality.
Run the following:
```c++
g++ hashtable.cpp, hashtabletest.cpp -o hashtable.o
```


