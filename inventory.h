// ------------------------------- inventory.h ---------------------------------
// Team Blockbuster - CS502 A WTR24
// Creation 20240223
// Modified N/A
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the Inventory class
// Assumptions - N/A
// ----------------------------------------------------------------------------
#ifndef INVENTORY_H
#define INVENTORY_H
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include "hashtable.h"
#include "product.h"
#include "media.h"
#include "movie.h"
#include "genre.h"

using namespace std;

class Inventory{
    private:
        // Denotes the name of the store inventory 
        string Name;
        // Address of the store
        string Address;
        // Maps customers to their ID
        HashTable customers;

        // Stores all possible products. E.g (Media, Hardware, etc)
        list<Product> productList;

        // ---------------------------------------------------------------------
        // getProduct()
        // Searches the product list by the abbreviation and returns address it 
        // there is one
        // Precondition: NONE
        // Postcondition: returns pointer to Product or null
        Product* getProduct(const string);

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
        // Ingests from automated backup files that have been output and stored.
        // Precondition: NONE
        // Postcondition: returns true if successfull, false otherwise
        bool ingestFromBackupFiles();

        // --------------------------------------------------------------------
        // command()
        // Executes commands from the console and calls the correct method. 
        // Returns true if command is executed, false if user wants to exit. 
        // Handles bad inputs. 
        // Precondition: Inventoryis intialized correctly
        // Postcondition: Command is executed if it is a valid and exectues the 
        // correct associated action and errors if the command is not valid
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
        bool executeBorrow(const string);

        // 
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
        bool executeReturn(const string);

        // --------------------------------------------------------------------
        // displayInventory()
        // Executes an Inventory (‘I’) command. Outputs the inventory to the 
        // console 
        // Precondition: Inventory is initialized
        // Postcondition: outputs all inventory to the console in order and 
        // blank if there are no values
        bool displayInventory();

        // --------------------------------------------------------------------
        // displayHistory()
        // Executes a History (‘H’) command. Outputs the transaction log of a 
        // customer to the console given a customer ID 
        // Precondition: Empty string or valid customer id parameter
        // Postcondition: If param string is empty, display transactions 
        // for all customers.  Otherwise, display transactions for given id,
        // blank if no transactions.
        void displayHistory(const string) const;

        // --------------------------------------------------------------------
        // createProduct()
        // Creates a new Product using the Product class and specify type of 
        // product. (Movie, Music, hardware, etc)
        // Precondition: Inventory is initialized correctly
        // Postcondition: creates a new Product object for that product and
        // returns error if the product already exists
        bool createProduct(const string);

        // --------------------------------------------------------------------
        // createGenre()
        // Creates a new Genre Binary Search Tree. (Comedy, Classic, Drama, Etc)
        // Precondition: Inventory and Product are initialized correctly
        // Postcondition: creates a new genre BST if no genre exists with the 
        // same name
        bool createGenre(const string);

        // --------------------------------------------------------------------
        // createMovie()
        // Creates a new movie. Assumes Product is a movie, based on genre the 
        // string is parsed differently so input is left generic
        // Precondition: Inventory, Product, and Genre are initialized correctly
        // Postcondition: creates a new node that designates the stock in 
        // inventory if it does not already exist
        bool createMovie(const string);

        // --------------------------------------------------------------------
        // createCustomer()
        // Creates a new customer in the hash table
        // Precondition: The Inventory and customer table are initialized 
        // correctly
        // Postcondition: creates a new customer in table if does not exist
        bool createCustomer(const string);

        // --------------------------------------------------------------------
        // createTransaction()
        // Creates a new transaction in the HashTable. ID is created off of date
        // customer ID and all other details.
        // Precondition: Customer id, mediaKey, and isReturn parameters
        // Postcondition: a new transaction transaction is created in the table
        // if the customer exists
        bool addTransaction(int, string, bool);

        // --------------------------------------------------------------------
        // commandInputFromFile(string)
        // reads and executes commands from command file
        // Precondition: NONE
        // Postcondition: all valid commands are executed
        void commandInputFromFile(const string);

};

#endif