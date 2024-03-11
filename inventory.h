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
        // Denotes the name of the store inventory 
        string Name;
        // Address of the store
        string Address;
        // Maps customers to their ID
        HashTable customers;
        // Stores all possible products. E.g (Media, Hardware, etc)
        vector<Product> Products;

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
        // looks at the predetermined paths for any .bak files that contain previous iteration
        // of inventories. 
        // Returns true if there are files

        // --------------------------------------------------------------------
        // ingestFromBackupFiles()
        // Ingests from automated backup files that have been outputted and stored.
        // Precondition: NONE
        // Postcondition: returns true if successfull, false otherwise
        bool ingestFromBackupFiles();
        // calls checkForBackupFiles() to verify there are files to ingest
        // if true
        // grab one file
        // create a new Inventory object
        // set the name and address from the file
        // iterate until there are no products left to create
        // iterate until there are no genres left to create
        // iterate until all movies have been inserted
        // return true if capable

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
        // creates file 
        // iterates through all products if there are any and outputs all values
        // into the file
        // iterates through all genres if there are any and outputs there values into the file
        // iterates through all genre BSTs and outputs the movie values in-order into the file

        // --------------------------------------------------------------------
        // command()
        // Executes commands from the console and calls the correct method. 
        // Returns true if command is executed, false if user wants to exit. 
        // Handles bad inputs. 
        // Precondition: Inventoryis intialized correctly
        // Postcondition: Command is executed if it is a valid command and exectues
        // the correct associated action and errors if the command is not valid
        void command(const string);
        // get the first character in the command to designate which method to call
        // switch(character)
        //      call method to execute that command

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
        void executeBorrow(const vector<string>);
        // searches the given string for information on the product
        // call getProduct() and if not nullptr
        // gets from the given string the Genre abbreviation
        // calls getGenre() and if not nullptr
        // gets from the given string the movie identification details using the
        // parsing infor from the Genre class gets the details.
        // calls getMovie() and if not nullptr
        // reduces the stock by 1
        // creates new transaction by utilizing borrowTransaction()

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
        void executeReturn(const vector<string>);
        // searches the given string for information on the product
        // call getProduct() and if not nullptr
        // gets from the given string the Genre abbreviation
        // calls getGenre() and if not nullptr
        // gets from the given string the movie identification details using the
        // parsing infor from the Genre class gets the details.
        // calls getMovie() and if not nullptr
        // increases the stock by 1
        // if nullptr, creates a new movie in that spot
        // creates new transaction by utilizing returnTransaction()

        // --------------------------------------------------------------------
        // displayInventory()
        // Executes an Inventory (‘I’) command. Outputs the inventory to the 
        // console 
        // Precondition: Inventory is initialized
        // Postcondition: outputs all inventory to the console in order and blank
        // if there are no values
        void displayInventory();
        // iterate through all products if they exist
        // iterate through all genres if they exist
        // iterate through all trees
        // output movie information and their stock

        // --------------------------------------------------------------------
        // displayHistory()
        // Executes a History (‘H’) command. Outputs the transaction log of a 
        // customer to the console given a customer ID 
        // Precondition: Empty string or valid customer id parameter
        // Postcondition: If param string is empty, display transactions 
        // for all customers.  Otherwise, display transactions for given id,
        // blank if no transactions.
        void displayHistory(const vector<string> terms) const;
        // scans customer ID from terms
        // scans through all customers for customer ID
        // given customer IDiterates through all the customer transactions 
        // output the transaction to the console.

        // --------------------------------------------------------------------
        // createProduct()
        // Creates a new Product using the Product class and specify type of 
        // product. (Movie, Music, hardware, etc)
        // Precondition: Inventory is initialized correctly
        // Postcondition: creates a new Product object for that product and
        // returns error if the product already exists
        void createProduct(string);
        // call getProduct() and if returns nullptr
        // create new Product object
        // set the name of the product
        // add the product to the list

        // --------------------------------------------------------------------
        // createGenre()
        // Creates a new Genre Binary Search Tree. (Comedy, Classic, Drama, Etc)
        // Precondition: Inventory and Product are initialized correctly
        // Postcondition: creates a new genre BST if no genre exists with the same name
        void createGenre(string);
        // call getGenre() and if returns nullptr
        // create new Genre object
        // set the name of the product
        // add the Genre to the list

        // --------------------------------------------------------------------
        // createMovie()
        // Creates a new movie. Assumes Product is a movie, based on genre the 
        // string is parsed differently so input is left generic
        // Precondition: Inventory, Product, and Genre are initialized correctly
        // Postcondition: creates a new node that designates the stock in inventory
        // if it does not already exist
        void createMovie(string);
        // // call getMovie() and if returns address
        // if nullptr towards comparison, create new movie
        // if found movie of same name return error

        // --------------------------------------------------------------------
        // createCustomer()
        // Creates a new customer in the hash table
        // Precondition: The Inventory and customer table are initialized correctly
        // Postcondition: creates a new customer in the table if it does not exist
        void createCustomer(string);
        // call get getCustomer() if returns nullptr
        // create new customer
        // else error to console

        // --------------------------------------------------------------------
        // createTransaction()
        // Creates a new transaction in the HashTable. ID is created off of date
        // customer ID and all other details.
        // Precondition: Customer id, mediaKey, and isReturn parameters
        // Postcondition: a new transaction transaction is created in the table
        // if the customer exists
        void addTransaction(int, string, bool);
        // call getMovie() if address returned
        // call getCustomer() if customer returned
        // call borrowStock() if isReturn is false, otherwise returnStock()
        // create a transaction in the list

        // --------------------------------------------------------------------
        // movieInputFromFile(string)
        // reads file and constructs genre BSTs
        // Precondition: NONE
        // Postcondition: genre BSTs are initialized for data lookup
        void movieInputFromFile();
        // iterates through a file until EOF
        // utilizes createMovie()

        // --------------------------------------------------------------------
        // customerInputFromFile(string)
        // reads file and initializes customer hashtable
        // Precondition: NONE
        // Postcondition: hashtable is ready for transaction lookup by 
        // customer id
        void customerInputFromFile();
        // iterates through a file until EOF
        // utilizes createCustomer()

        // --------------------------------------------------------------------
        // commandInputFromFile(string)
        // reads and executes commands from command file
        // Precondition: NONE
        // Postcondition: all valid commands are executed
        void commandInputFromFile();
        // iterates through a file until EOF
        // utilizes createCommand()
};
