// ------------------------------- inventory.h ----------------------------------
// Team Blockbuster - CS502 A WTR24
// Creation 20240223
// Modified N/A
// ----------------------------------------------------------------------------
// Summary - This file contains the specification for the Inventory class
// Assumptions - N/A
// ----------------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include "hashtable.h"
#include "product.h"
#include "movie.h"
#include "genre.h"

using namespace std;

class Inventory{
    private:
        // Transaction
        // Used to contain the information within a borrow or return 
        // transaction. This is the ValueType of the Transactions HashTable
        // TransactionID is the KeyType of the Transactions HashTable.
        struct Transaction {
            int transactionID;
            string borrowDate;
            string nodeID;
            string dueDate;
            string returnDate;
            string transactionDetail;
        };
        // Customer
        // Used to contain customer information.
        // This is the ValueType of the Customers HashTable
        // ID is the KeyType of the Customers HashTable.
        // The customer entry will also contain their associated open and 
        // closed transactions as a list of transactionIDs.
        struct Customer {
            int ID;
            string Name;
            string DateCreated;
            int infractionCount;
            bool banned;
            list<Transaction> openTransactions;
            list<Transaction> closedTransactions;
        };
        // Denotes the name of the store inventory 
        string Name;
        // Address of the store
        string Address;
        // Maps customers to their ID
        HashTable<int, Customer> *Customers;
        // Maps Open transactions to their ID
        HashTable<int, Transaction> *OpenTransactions;
        // Maps Closed transactions to their ID
        HashTable<int, Transaction> *ClosedTransactions;
        // Stores all possible products. E.g (Media, Hardware, etc)
        list<Product> Products;

    public:

        // --------------------------------------------------------------------
        // Default Constructor
        // Precondition: NONE
        // Postcondition: Initialized Inventory with no name or address.
        Inventory();
        // --------------------------------------------------------------------
        // Name and Address Constructor (Name, Address)
        // Initialize inventory from backup files.  If files don't exist,
        // initialize empty inventory with name & address fields
        // Precondition: NONE
        // Postcondition: Initialized Inventory w/ name and address.
        Inventory(const string, const string);
        // --------------------------------------------------------------------
        // Command File Constructor
        // Initialize Inventory with specified name and address, build customer 
        // and movies list. Then execute commands from file.
        // If any files are non-existing, return error.
        // Precondition: NONE
        // Postcondition: Initialized inventory.
        Inventory(
            const string, const string, const string, const string, const string);
        // --------------------------------------------------------------------
        // Copy Constructor
        // Deep copies inventory
        // Precondition: Inventory to be copied should exist.
        // Postcondition: Deep copied inventory.
        Inventory(const Inventory &);
        // --------------------------------------------------------------------
        // Destructor
        // Frees dynamically allocated memory from HashTables and Genre BSTs
        // Precondition: NONE
        // Postcondition: Dynamic memory freed
        ~Inventory();
        // --------------------------------------------------------------------
        // setName
        // Set inventory name field
        // Precondition: NONE
        // Postcondition: Name field is updated w/ value
        void setName(string);
        // --------------------------------------------------------------------
        // getName
        // Get inventory name field
        // Precondition: NONE
        // Postcondition: return name field value
        string getName();
        // --------------------------------------------------------------------
        // setAddress
        // Set inventory address field
        // Precondition: NONE
        // Postcondition: Address field is updated w/ value
        void setAddress(string);
        // --------------------------------------------------------------------
        // getAddress
        // Get inventory address field
        // Precondition: NONE
        // Postcondition: return address field value
        string getAddress();
        // --------------------------------------------------------------------
        // checkForBackupFiles()
        // Returns whether there are automated backup files of previous 
        // sessions
        // Precondition: NONE
        // Postcondition: return true if files exist, false otherwise
        bool checkForBackupFiles();
        // --------------------------------------------------------------------
        // ingestFromBackupFiles()
        // Ingests from automated backup files that have been outputted and stored.
        // Precondition: NONE
        // Postcondition: returns true if successfull, false otherwise
        bool ingestFromBackupFiles();
        // --------------------------------------------------------------------
        // dumpToBackupFiles()
        // Dumps genre nodes in-order into a <inventoryName_movie_dump.bak> 
        // Dumps transactions into <inventoryName_transactions_dump.bak>
        // Dumps customers into <inventoryName_customers_dump.bak>
        // Allows us to save the state of the inventory
        // between application sessions. (ex: customer or movies are manually 
        // added) Automated Backs up all data structures to files
        // Returns success
        // Precondition: NONE
        // Postcondition: Overwrites file if file named with 
        // inventoryName_*dumpType*_dump.bak exists
        bool dumpToBackupFiles();
        // --------------------------------------------------------------------
        // command()
        // Executes commands from the console and calls the correct method. 
        // Returns true if command is executed, false if user wants to exit. 
        // Handles bad inputs. 
        // Precondition: Inventoryis intialized correctly
        // Postcondition: Command is executed if it is a valid command and exectues
        // the correct associated action and errors if the command is not valid
        void command(const string);

        // --------------------------------------------------------------------
        // executeBorrow()
        // Executes a borrow transaction. (subtract 1 from inventory)
        // Also updates the Transaction Log via. addTransactionBorrow()
        // Comment: May need to handle erronous data such as invalid user or 
        // invalid movies
        // Executes a Borrow (‘B’) command. Inserts a new transaction into log 
        // Precondition: command is valid and inventory is initialized correctly
        // and the movie is in stock
        // Postcondition: stock is decreased by one and a transaction is created
        // in the transaction log and errors out if command is not valid
        void executeBorrow();

        // --------------------------------------------------------------------
        // executeReturn()
        // Executes a return transaction. (adds 1 to inventory)
        // Also updates the Transaction Log via. addTransactionReturn()
        // Comment: May need to handle erronous data such as invalid user or 
        // invalid movies
        // Executes a Return (‘R’) command. Gets the transaction from the log 
        // and changes the return date. Calculates fees due on return. 
        // Precondition: command is valid and inventory is initialized correctly
        // Postcondition: stock is decreased by one and a transaction is created
        // in the transaction log and errors out if command is not valid
        void executeReturn();

        // --------------------------------------------------------------------
        // displayInventory()
        // Executes an Inventory (‘I’) command. Outputs the inventory to the 
        // console 
        // Precondition: Inventory is initialized
        // Postcondition: outputs all inventory to the console in order and blank
        // if there are no values
        void displayInventory();

        // --------------------------------------------------------------------
        // displayHistory()
        // Executes a History (‘H’) command. Outputs the transaction log of a 
        // customer to the console given a customer ID 
        // Precondition: NONE
        // Postcondition: displays all transactions for all customers and blank
        // if no transactions.
        void displayHistory();

        // --------------------------------------------------------------------
        // createProduct()
        // Creates a new Product using the Product class and specify type of 
        // product. (Movie, Music, hardware, etc)
        // Precondition: Inventory is initialized correctly
        // Postcondition: creates a new Product object for that product and
        // returns error if the product already exists
        void createProduct(string);

        // --------------------------------------------------------------------
        // removeProduct()
        // Removes a product using the product class
        // Precondition: Inventory must be initialized correctly
        // Postcondition: removes the product from the product list if it exists
        // skips if it doesn't exist
        void removeProduct(string);

        // --------------------------------------------------------------------
        // getProduct()
        // Iterates through the list to get the product needed.
        // Precondition: Inventory is initialized correctly
        // Postcondition: returns the address of the product if it exists, null if it doesn't
        Product getProduct(string);

        // --------------------------------------------------------------------
        // createGenre()
        // Creates a new Genre Binary Search Tree. (Comedy, Classic, Drama, Etc)
        // Precondition: Inventory and Product are initialized correctly
        // Postcondition: creates a new genre BST if no genre exists with the same name
        void createGenre(string);

        // --------------------------------------------------------------------
        // removeGenre()
        // Removes a genre from the list
        // Precondition: Inventory and Product are initialized correctly
        // Postcondition: Genre is removed if it exists
        void removeGenre(string);

        // --------------------------------------------------------------------
        // getGenre()
        // Iterates through the list of Genre heads to return the given Genre 
        // Binary Search Tree
        // Precondition: Inventory and Product are initialized correctly
        // Postcondition: returns the address of the Genre if the Genre exists and errors out
        Genre getGenre(string);

        // --------------------------------------------------------------------
        // createMovie()
        // Creates a new movie. Assumes Product is a movie, based on genre the 
        // string is parsed differently so input is left generic
        // Precondition: Inventory, Product, and Genre are initialized correctly
        // Postcondition: creates a new node that designates the stock in inventory
        // if it does not already exist
        void createMovie(string);

        // --------------------------------------------------------------------
        // removeMovie()
        // Removes a movie from the binary tree
        // Precondition: Inventory, Product, and Genre are initialized correctly
        // Postcondition: removes a movie node if it exists
        void removeMovie(string);

        // --------------------------------------------------------------------
        // getMovie()
        // Gets the movie based on the input
        // Precondition: Inventory, Product, and Genre are initialized correctly
        // Postcondition: the address of the movie is returned
        Movie getMovie(string);

        // --------------------------------------------------------------------
        // createCustomer()
        // Creates a new customer in the hash table
        // Precondition: The Inventory and customer table are initialized correctly
        // Postcondition: creates a new customer in the table if it does not exist
        void createCustomer(int);

        // --------------------------------------------------------------------
        // removeCustomer()
        // Deletes customer from Hash table
        // Precondition: The Inventory and customer table are initialized correctly
        // Postcondition: removes a customer from the customer table if it exists
        void removeCustomer(int);

        // --------------------------------------------------------------------
        // getCustomer(int)
        // Gets the customer based on ID
        // Return NULL if customer not found?
        // Precondition: The Inventory and customer table are initialized correctly
        // Postcondition: returns the customer address in the hash table
        void getCustomer(int);

        // --------------------------------------------------------------------
        // createTransaction()
        // Creates a new transaction in the HashTable. ID is created off of date
        // customer ID and all other details.
        // Precondition: inventory and customer table are initialized correctly
        // Postcondition: a new transaction borrow transaction is created in the table
        // if the customer exists
        void borrowTransaction();

        // --------------------------------------------------------------------
        // returnTransaction()
        // Sets the transaction return date of an existing transaction
        // Precondition: inventory and customer table are initialized correctly
        // Postcondition: a return transaction is created if the customer exists
        // and fees are calculated
        void returnTransaction();

        // --------------------------------------------------------------------
        // removeTransaction()
        // Removes the transaction from the HashTable
        // Precondition: inventory and customer table are initialized correctly
        // Postcondition: transaction is removed if the transaction exists
        void removeTransaction();

        // --------------------------------------------------------------------
        // movieInputFromFile(string)
        // reads file and constructs genre BSTs
        // Precondition: NONE
        // Postcondition: genre BSTs are initialized for data lookup
        void movieInputFromFile(string);

        // --------------------------------------------------------------------
        // customerInputFromFile(string)
        // reads file and initializes customer hashtable
        // Precondition: NONE
        // Postcondition: hashtable is ready for transaction lookup by 
        // customer id
        void customerInputFromFile(string);
        
        // --------------------------------------------------------------------
        // commandInputFromFile(string)
        // reads and executes commands from command file
        // Precondition: NONE
        // Postcondition: all valid commands are executed
        void commandInputFromFile(string);
};
