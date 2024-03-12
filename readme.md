# [CSS 502] Assignment 4 Rent-a-Reel

## Implementation Contributions
- David Li - 100% Hashtable implementation, testing, and documentation. Additionally some inventory methods related to Hashtable. Contributed to Readme documentation.
- Darren Husting - 75% of Inventory 100% of Product, Media, and Genre. Contributed to Readme documentation.
- AJ Plumlee - Genre (Binary Search Tree), NodeData & Movie class implementations and documentation.  Also debugged Inventory class. Contributed to Readme documentation.

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

### Customer
```
struct Customer
{
    int ID = 0;
    string name;
    string dateCreated;
    int infractionCount;
    bool banned;
    list<Transaction> transactions;
};
```

### Transaction
```
struct Transaction
{
    string transactionID;
    string borrowDate;
    string dueDate;
    string returnDate;
    string transactionDetail;
};
```

### KeyValuePair
Elements of the hashtable
```
struct KeyValuePair
{
    int customerID = 0;
    Customer customer;
};
```

Although the prompt specifies customerIDs from 0000 to 9999. The array is limited to 1000 entries to utilize and demonstrate the closed hash table.
> Note: The intent is that there may be 10000 customers however at any one location (`inventory` object) there may only ever be up to around 1000 customers.
> The application is designed to be scalable. If the customer base decides to go must larger than 10000, we can scale the array size accordingly.

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
// Display up to 10 customers and 20 transactions per customer
hashTable.display(10, 20);

// Display up to 10 customers w/o transactions
hashTable.display(10);
```

#### To Display Details and Transaction history of Customer
```
// Display transaction history of customer1 up to 1000 entries. (limit of hash table)
hashTable.displayHistory(customer1.ID);
```

### To test the hashtable class functionality.
`hashTableTest.cpp` contains driver code to test the hashtable functionality.
#### To Build
```c++
g++ hashtable.cpp, hashTableTest.cpp -o hashtable.o
```
#### To run
```
./hashtable.o
```

