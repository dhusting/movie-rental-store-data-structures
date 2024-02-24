// ------------------------------- inventory.h ----------------------------------
// Team Blockbuster - CS502 A WTR24
// Creation 20240223
// Modified N/A
// ----------------------------------------------------------------------------
// Summary - This file contains the specification for the Inventory class
// Assumptions - N/A
// ----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Inventory{
    private:
        // Denotes the name of the store inventory 
        string Name;
        // Address of the store
        string Address;
        // Contains all OPEN transactions within the store. Needs to create a 
        // transaction when a borrow occurs, set a due date,  
        HashTable<Transactions> OpenTransactions;
        // Contains all CLOSED transactions within the store. Closed 
        // transactions are given a return date from an open transaction from 
        // the hash table and moved to the closed  
        HashTable<Transaction> ClosedTransactions;
        // Customer table will hold all important information about a customer 
        HashTable<Transaction> Customers;
        HashTable<CustId, TransId> Rel;
        // Stores all possible products. E.g (Media, Hardware, etc)
        List<Product> Products;

    public:
        // --------------------------------------------------------------------
        // Default Constructor
        // Precondition: TBD
        // Postcondition: TBD
        Inventory();
        // --------------------------------------------------------------------
        // Name and Address Constructor (Name, Address)
        // Precondition: TBD
        // Postcondition: TBD
        Inventory(string, string);
        // --------------------------------------------------------------------
        // Command File Constructor
        // (Name, Address, CustomerFile, MovieFile, CommandFile)
        // Precondition: TBD
        // Postcondition: TBD
        Inventory(string, string, string, string, string);
        // --------------------------------------------------------------------
        // Copy Constructor
        Inventory(const Inventory &);
        // --------------------------------------------------------------------
        // Destructor
        ~Inventory();
        // --------------------------------------------------------------------
        // checkForFiles()
        // Returns whether there are automated backup files of previous 
        // iterations
        // Precondition: TBD
        // Postcondition: TBD
        bool checkForFiles();
        // --------------------------------------------------------------------
        // ingestFromFiles()
        // Ingests from automated backup files that have been outputted and stored.
        // Returns success
        // Precondition: TBD
        // Postcondition: TBD
        bool ingestFromFiles();
        // --------------------------------------------------------------------
        // dumpToFile()
        // Outputs/Updates formatted files: data4movies.txt, data4customers.txt.
        // Note: This essentially allows us to save the state of the data 
        // between application sessions. (ex: customer or movies are manually 
        // added) Automated Backs up all data structures to files
        // Returns success
        // Precondition: TBD
        // Postcondition: TBD
        bool dumpToFile();
        // --------------------------------------------------------------------
        // command()
        // Inputs commands from the console and calls the correct method. 
        // Returns true if command is executed, false if user wants to exit. 
        // Handles bad inputs. 
        // Precondition: TBD
        // Postcondition: TBD 
        void command();

        // --------------------------------------------------------------------
        // executeBorrow()
        // Executes a borrow transaction. (subtract 1 from inventory)
        // Also updates the Transaction Log via. addTransactionBorrow()
        // Comment: May need to handle erronous data such as invalid user or 
        // invalid movies
        // Executes a Borrow (‘B’) command. Inserts a new transaction into log 
        // Precondition: TBD
        // Postcondition: TBD
        void executeBorrow();

        // --------------------------------------------------------------------
        // executeReturn()
        // Executes a return transaction. (adds 1 to inventory)
        // Also updates the Transaction Log via. addTransactionReturn()
        // Comment: May need to handle erronous data such as invalid user or 
        // invalid movies
        // Executes a Return (‘R’) command. Gets the transaction from the log 
        // and changes the return date. Calculates fees due on return. 
        // Precondition: TBD
        // Postcondition: TBD
        void executeReturn();

        // --------------------------------------------------------------------
        // displayInventory()
        // Executes an Inventory (‘I’) command. Outputs the inventory to the 
        // console 
        // Comment: How do we want to format this? Table? What columns?
        // Precondition: TBD
        // Postcondition: TBD
        void displayInventory();

        // --------------------------------------------------------------------
        // displayHistory()
        // Executes a History (‘H’) command. Outputs the transaction log of a 
        // customer to the console given a customer ID 
        // Precondition: TBD
        // Postcondition: TBD
        void displayHistory();

        // --------------------------------------------------------------------
        // createProduct()
        // Creates a new Product using the Product class and specify type of 
        // product. (Movie, Music, hardware, etc)
        // Precondition: TBD
        // Postcondition: TBD
        void createProduct();

        // --------------------------------------------------------------------
        // removeProduct()
        // Removes a product using the product class
        // Precondition: TBD
        // Postcondition: TBD
        void removeProduct();

        // --------------------------------------------------------------------
        // getProduct()
        // Iterates through the list to get the product needed.
        // Precondition: TBD
        // Postcondition: TBD
        void getProduct();

        // --------------------------------------------------------------------
        // createGenre()
        // Creates a new Genre Binary Search Tree. (Comedy, Classic, Drama, Etc)
        // Precondition: TBD
        // Postcondition: TBD
        void createGenre();

        // --------------------------------------------------------------------
        // removeGenre()
        // Removes a genre from the list
        // Precondition: TBD
        // Postcondition: TBD
        void removeGenre();

        // --------------------------------------------------------------------
        // getGenre()
        // Iterates through the list of Genre heads to return the given Genre 
        // Binary Search Tree
        // Precondition: TBD
        // Postcondition: TBD
        void getGenre();

        // --------------------------------------------------------------------
        // createMovie()
        // Creates a new movie. Assumes Product is a movie, based on genre the 
        // string is parsed differently so input is left generic
        // Precondition: TBD
        // Postcondition: TBD
        void createMovie();

        // --------------------------------------------------------------------
        // removeMovie()
        // Removes a movie from the binary tree
        // Precondition: TBD
        // Postcondition: TBD
        void removeMovie();

        // --------------------------------------------------------------------
        // getMovie()
        // Gets the movie based on the input
        // Precondition: TBD
        // Postcondition: TBD
        void getMovie();

        // --------------------------------------------------------------------
        // createCustomer()
        // Creates a new customer in the hash table
        // Precondition: TBD
        // Postcondition: TBD
        void createCustomer();

        // --------------------------------------------------------------------
        // removeCustomer()
        // Deletes customer from Hash table
        // Precondition: TBD
        // Postcondition: TBD
        void removeCustomer();

        // --------------------------------------------------------------------
        // getCustomer(int)
        // Gets the customer based on ID
        // Return NULL if customer not found?
        // Precondition: TBD
        // Postcondition: TBD
        void getCustomer(int);

        // --------------------------------------------------------------------
        // getCustomer(string)
        // Gets the customer based on name
        // Return NULL if customer not found?
        // Precondition: TBD
        // Postcondition: TBD
        void getCustomer(string);

        // --------------------------------------------------------------------
        // createTransaction()
        // Creates a new transaction in the HashTable. ID is created off of date
        // customer ID and all other details.
        // Precondition: TBD
        // Postcondition: TBD
        void createTransaction();

        // --------------------------------------------------------------------
        // returnTransaction()
        // Sets the transaction return date of an existing transaction
        // Precondition: TBD
        // Postcondition: TBD
        void returnTransaction();

        // --------------------------------------------------------------------
        // removeTransaction()
        // Removes the transaction from the HashTable
        // Comment: Suggest transaction has an ID and you remove the transaction
        // based on ID, not (String customerID, String productName, String 
        // genreName, String input)
        // Precondition: TBD
        // Postcondition: TBD
        void removeTransaction();

        

}
