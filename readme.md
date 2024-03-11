# Header 1
## HashTable
The hashtable is based on the closed hashing concept. 
It uses an array of keyvaluepair structs with customerID as the key and customer as a value.

### How to use
#### Initialize HashTable
```
// Instantiate the HashTable
HashTable hashTable;
```

#### Initialize customers to insert
```
// Create some sample customers
Customer customer1{1, "John Doe", "2024-03-01", 0, false, {}};
Customer customer2{2, "Jane Smith", "2024-03-02", 0, false, {}};
Customer customer3{3, "Alice Johnson", "2024-03-03", 0, false, {}};
```

#### Insert customers into table
```
// Insert customers into the hash table
hashTable.insert(customer1.ID, customer1);
hashTable.insert(customer2.ID, customer2);
hashTable.insert(customer3.ID, customer3);
```

#### To retrieve
```
Customer* retrievedCustomer = hashTable.get(2);
cout << "Retrieved Customer: " << retrievedCustomer->name << endl;
```

#### To remove
```
bool removed = hashTable.remove(2); 
if (removed) {
    cout << "Customer removed successfully." << endl;
} else {
    cout << "Customer not found." << endl;
}
```


#### To display
```
// Display hash table contents
cout << "HashTable contents:" << endl;
hashTable.display(10); // Display up to 10 elements for demonstration
cout << "-----------------------------------" << endl;
```

### To test the hashtable class functionality.

`hashtabletest.cpp` contains driver code to test the hashtable functionality.
Run the following:
```c++
g++ hashtable.cpp, hashtabletest.cpp -o hashtable.o
```


