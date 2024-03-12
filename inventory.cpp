// ------------------------------- inventory.cpp -------------------------------
// Team Blockbuster - CS502 A
// Created 20240304
// Modified 20240304
// -----------------------------------------------------------------------------
// Summary - This file contains the implementation for the Inventory class
// Assumptions - N/A
// -----------------------------------------------------------------------------
#include <fstream>
#include <iostream>
#include <filesystem>
#include <list>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include "inventory.h"

using namespace std;

// -----------------------------------------------------------------------------
// Default Constructor
// Precondition: NONE
// Postcondition: Initialized Inventory with no name or address.
Inventory::Inventory() {}

// -----------------------------------------------------------------------------
// Name and Address Constructor (Name, Address)
// Initialize inventory from backup files.  If files don't exist,
// initialize empty inventory with name & address fields
// Precondition: NONE
// Postcondition: Initialized Inventory w/ name and address.
Inventory::Inventory(const string name, const string address) {
    Name = name;
    Address = address;
}

// -----------------------------------------------------------------------------
// Command File Constructor
// Initialize Inventory with specified name and address, build customer 
// and movies list. Then execute commands from file.
// If any files are non-existing, return error.
// Precondition: NONE
// Postcondition: Initialized inventory.
Inventory::Inventory(const string name, const string address, const string iPath
    , const string aPath, const string cPath) {
        Name = name;
        Address = address;
}

// -----------------------------------------------------------------------------
// Copy Constructor
// Deep copies inventory
// Precondition: Inventory to be copied should exist.
// Postcondition: Deep copied inventory.
Inventory::Inventory(const Inventory &) {}
// TODO: Deep copy customers table?

// -----------------------------------------------------------------------------
// Destructor
// Frees dynamically allocated memory from HashTables and Genre BSTs
// Precondition: NONE
// Postcondition: Dynamic memory freed
Inventory::~Inventory() {}

// -----------------------------------------------------------------------------
// setName
// Set inventory name field
// Precondition: NONE
// Postcondition: Name field is updated w/ value
void Inventory::setName(string name) {
    Name = name;
}

// -----------------------------------------------------------------------------
// getName
// Get inventory name field
// Precondition: NONE
// Postcondition: return name field value
string Inventory::getName() {
    return Name;
}

// -----------------------------------------------------------------------------
// setAddress
// Set inventory address field
// Precondition: NONE
// Postcondition: Address field is updated w/ value
void Inventory::setAddress(string address) {
    Address = address;
}

// -----------------------------------------------------------------------------
// getAddress
// Get inventory address field
// Precondition: NONE
// Postcondition: return address field value
string Inventory::getAddress() {
    return Address;
}

// -----------------------------------------------------------------------------
// getProduct()
// Searches the product list by the abbreviation and returns address it there is one
// Precondition: NONE
// Postcondition: returns pointer to Product or null
Product* Inventory::getProduct(const string abbrev)
{
    //iterate through product list
    for(Product * product : productList)
    {
        //compare abbreviations and return address
        if(product->getAbbreviation() == abbrev) {
            
            return product;
            
        }

    }

    return nullptr;

}

Media * Inventory::getMedia(const string abbrev)
{
    //iterate through product list
    for(Product * product : productList)
    {

        if (Media * mediaPtr = (Media *)product)
        {
            //compare abbreviations and return address
            if(mediaPtr->getAbbreviation() == abbrev) {
            
                return mediaPtr;
            
            }
        }

    }

    return nullptr;

}

// -----------------------------------------------------------------------------
// checkForBackupFiles()
// Returns whether there are automated backup files of previous 
// sessions
// Precondition: NONE
// Postcondition: return true if files exist, false otherwise
bool Inventory::checkForBackupFiles() 
{
    return filesystem::exists("backup.bak");
}
// looks at the predetermined paths for any .bak files that contain previous iteration
// of inventories. 
// Returns true if there are files

// -----------------------------------------------------------------------------
// ingestFromBackupFiles()
// Ingests from automated backup files that have been outputted and stored.
// Precondition: NONE
// Postcondition: returns true if successfull, false otherwise
bool Inventory::ingestFromBackupFiles() 
{
    //check for the backup file
    if (checkForBackupFiles())
    {
        //create empty variables for storage
        string line;
        ifstream commandFile;

        //open the file
        commandFile.open("backup.bak");

        //get every line from the file
        while (getline(commandFile, line))
            //call the command function for every line
            command(line);

        //close the file
        commandFile.close();
    }
}

// -----------------------------------------------------------------------------
// command()
// Executes commands from the console and calls the correct method. 
// Returns true if command is executed, false if user wants to exit. 
// Handles bad inputs. 
// Precondition: Inventoryis intialized correctly
// Postcondition: Command is executed if it is a valid command and exectues
// the correct associated action and errors if the command is not valid
void Inventory::command(const string line) {
    // parse input line
    char term = line.at(0);
    
    //find the first comma location
    int firstComma = line.find(',');

    //truncate the command abbreviation from the line
    string command = line.substr(firstComma+2);

    //set a command success flag that is false
    bool commandSuccessFlag = false;

    //if statement to shuttle command to the correct method
    if (term == 'P')
        commandSuccessFlag = createProduct(command);
    else if (term == 'G')
        commandSuccessFlag = createGenre(command);
    else if (term == 'B')
        commandSuccessFlag = executeBorrow(command);
    else if (term == 'R')
        commandSuccessFlag = executeReturn(command);
    else if (term == 'I')
        displayInventory();
    else if (term == 'H')
        displayHistory(command);
    //if first char is digit, assume creation of customer
    else if (isdigit(term))
        commandSuccessFlag = createCustomer(line);
    else {
        //default to creating a movie
        commandSuccessFlag = createMovie(line);
    }

    //check to see if a storage command was executed
    if(commandSuccessFlag)
    {   
        //open a new file output stream
        ofstream outputFile("backup.bak");

        //if the file is open
        if (outputFile.is_open())
        {
            //output line to the file
            outputFile << line << endl;

            //close the file
            outputFile.close();
        }

    }
}

// -----------------------------------------------------------------------------
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
bool Inventory::executeBorrow(const string command) 
{
    //vector to easily grab the values of the command
    vector<string> commandFields;

    //string stream to parse each word in the line
    stringstream ss(command);

    //variables to temp store the words and id
    string word;
    string id;

    //count number of spaces
    int spaceCount = 0;

    // Parse the string and grab each word up to the 4th space
    while (ss >> word && spaceCount < 2) {
        //increase count if word is a space
        if (word == " ") {
            spaceCount++;
        } else {
            //add the word to the commandfields vector
            commandFields.push_back(word);
        }
    }

    //store the rest of the words in the id
    while (ss >> id);

    //create an int for the customer id
    int customerID = stoi(commandFields.at(0));

    //search for the customer by the id
    Customer * customer = customers.get(customerID);

    //check to see if customer exists
    if(customer != nullptr)
    {
        //search for the product
        Product * product = getProduct(commandFields.at(1));

        //check to see if the product exists
        if (product != nullptr)
        {

            //test to see if the product is a media
            if (Media * mediaPtr = dynamic_cast<Media *>(product))
            {
                //search for the genre
                Genre * genre = mediaPtr->getGenre(commandFields.at(2));

                //check to see if the genre exists
                if (genre != nullptr)
                {
                    //empty NodeData to store address if the Node is found
                    NodeData * node;
                    
                    //search for the node with the movie id
                    genre->find(id, node);
                    
                    //reduce the stock by 1
                    if(!(node->borrowStock()))
                    {
                        cout << "Stock is already at 0" << endl;
                    }
                    
                    //create a transaction
                    addTransaction(customerID, command, false);
                }

            } else {
                cout << "Genre Abbreviation: " << commandFields.at(2) << " does not exist" << endl;
            }
        } else {
            cout << "Product Abbreviation: " << commandFields.at(1) << " does not exist" << endl;
        }
    } else {
        cout << "Customer ID: " << id << " does not exist" << endl;
    }

}

// -----------------------------------------------------------------------------
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
bool Inventory::executeReturn(const string command) 
{
    //vector to easily grab the values of the command
    vector<string> commandFields;

    //string stream to parse each word in the line
    stringstream ss(command);

    //variables to temp store the words and id
    string word;
    string id;

    //count number of spaces
    int spaceCount = 0;

    // Parse the string and grab each word up to the 4th space
    while (ss >> word && spaceCount < 2) {
        //increase count if word is a space
        if (word == " ") {
            spaceCount++;
        } else {
            //add the word to the commandfields vector
            commandFields.push_back(word);
        }
    }

    //store the rest of the words in the id
    while (ss >> id);

    //create an int for the customer id
    int customerID = stoi(commandFields.at(0));

    //search for the customer by the id
    Customer * customer = customers.get(customerID);

    //check to see if customer exists
    if(customer != nullptr)
    {
        //search for the product
        Product * product = getProduct(commandFields.at(1));

        //check to see if the product exists
        if (product != nullptr)
        {

            //test to see if the product is a media
            if (Media * mediaPtr = (Media *)product)
            {
                //search for the genre
                Genre * genre = mediaPtr->getGenre(commandFields.at(2));

                //check to see if the genre exists
                if (genre != nullptr)
                {
                    //empty NodeData to store address if the Node is found
                    NodeData* node;
                    
                    //search for the node with the movie id
                    genre->find(id, node);
                    
                    //reduce the stock by 1
                    node->returnStock();
                    
                    //create a transaction
                    addTransaction(customerID, command, false);
                }

            } else {
                cout << "Genre Abbreviation: " << commandFields.at(2) << " does not exist" << endl;
            }
        } else {
            cout << "Product Abbreviation: " << commandFields.at(1) << " does not exist" << endl;
        }
    } else {
        cout << "Customer ID: " << id << " does not exist" << endl;
    }
}

// -----------------------------------------------------------------------------
// displayInventory()
// Executes an Inventory (‘I’) command. Outputs the inventory to the 
// console 
// Precondition: Inventory is initialized
// Postcondition: outputs all inventory to the console in order and blank
// if there are no values
bool Inventory::displayInventory() {
    //checks to see if there are any products
    if (productList.size() == 0)
    {
        //output no products available
        cout << "No Products available" << endl;
        return false;
    }

    //iterate through all the in the list
    for (Product * product : productList)
    {

        //try to convert to media
        if (Media * mediaPtr = (Media *)product)
        {
            //call the print method
            mediaPtr->printGenres();
        }
        
    }
}

// -----------------------------------------------------------------------------
// displayHistory()
// Executes a History (‘H’) command. Outputs the transaction log of a 
// customer to the console given a customer ID 
// Precondition: Empty string or valid customer id parameter
// Postcondition: If param string is empty, display transactions 
// for all customers.  Otherwise, display transactions for given id,
// blank if no transactions.
void Inventory::displayHistory(const string term) const {
    // given customer ID
    // output the transaction to the console.
    int customerID = stoi(term);
    // Output up to 1000 transactions of given customer ID
    customers.displayHistory(customerID, 1000);
}

// -----------------------------------------------------------------------------
// createProduct()
// Creates a new Product using the Product class and specify type of 
// product. (Movie, Music, hardware, etc)
// Precondition: Inventory is initialized correctly
// Postcondition: creates a new Product object for that product and
// returns error if the product already exists
bool Inventory::createProduct(const string command) 
{
    vector<string> commandFields;
    string parsedField;

    //string stream to parse the command
    stringstream ss(command);

    //get every word separated by a comma
    while (getline(ss, parsedField, ',')) {
        //add to the field vector
        commandFields.push_back(parsedField);
    }

    //check to see if the product exists already
    if(getProduct(commandFields.at(0)) == nullptr)
    {
        //if the genre is of media type
        if (commandFields.at(0) == "M")
        {

            string abbrev = commandFields.at(1).substr(1);
            string name = commandFields.at(2).substr(1);

            //create a new media object giving it the abbreviation and name
            Media * m = new Media(abbrev, name);

            //add to the back of the list
            productList.push_back(m);
        }
    } else {
        cout << "Product Abbreviation: " << commandFields.at(1) << " does not exist" << endl;
    }
}

// -----------------------------------------------------------------------------
// createGenre()
// Creates a new Genre Binary Search Tree. (Comedy, Classic, Drama, Etc)
// Precondition: Inventory and Product are initialized correctly
// Postcondition: creates a new genre BST if no genre exists with the same name
bool Inventory::createGenre(const string command) {
    
    char abbrev = command.at(0);
    string str(1, abbrev);

    //search for the product giving it the abbreviation
    Product * product = getProduct(str);

    //check to see if the product exists
    if(product != nullptr)
    {
        //try to convert to a Media
        if(Media* mediaPtr = dynamic_cast<Media*>(product))
        {
            //get the rest of the command
            string genreCommand = command.substr(3);

            //call createGenre        
            mediaPtr->createGenre(genreCommand);
        }    

    } else {
        cout << "Product Abbreviation: " << command.at(0) << " does not exist" << endl;
    }
}

// -----------------------------------------------------------------------------
// createMovie()
// Creates a new movie. Assumes Product is a movie, based on genre the 
// string is parsed differently so input is left generic
// Precondition: Inventory, Product, and Genre are initialized correctly
// Postcondition: creates a new node that designates the stock in inventory
// if it does not already exist
bool Inventory::createMovie(const string line) {
    // parse input line
    stringstream ss(line);
    string abbrev;
    getline(ss, abbrev, ',');

    // get matching genre & insert input line
    Product *product = getProduct("D");    
    Media* mediaPtr = dynamic_cast<Media*>(product);
    Genre * genre = mediaPtr->getGenre(abbrev);
    if (genre == nullptr)
        return false;
    genre->insert(line);
    return true;
}

// -----------------------------------------------------------------------------
// createCustomer()
// Creates a new customer in the hash table
// Precondition: The Inventory and customer table are initialized correctly
// Postcondition: creates a new customer in the table if it does not exist
bool Inventory::createCustomer(string line) {
    // parse line for customer information
    // call get getCustomer() if returns nullptr
    // create new customer
    // else error to console
    stringstream ss(line);
    string term;
    string name;

    ss >> term;
    int customerID = stoi(term);
    name = ss.str();
    // TODO: programmatically set creation date
    Customer newCustomer{customerID, name, "2024-03-10", 0, false, {}};
    customers.insert(customerID, newCustomer);
    return true; // TODO: return success
}

// -----------------------------------------------------------------------------
// addTransaction()
// Transactions are either a borrow or return.
// If transaction is a borrow, creates a new transaction in the HashTable. 
// ID is created off of date customer ID and all other details.
// If transaction is a return, searches for the transaction given the customer
// ID and updates the return date.
// Transaction is moved to front of list to maintain chronological order. 
// Precondition: Customer id, transaction details, and isReturn parameters
// Postcondition: a new transaction transaction is created in the table
// if the customer exists
bool Inventory::addTransaction(int customerID, string details, bool isBorrow) {
    // call getMovie() if address returned
    // call getCustomer() if customer returned
    // call borrowStock() if isReturn is false, otherwise returnStock()
    // create a transaction in the list
    return customers.addTransaction(customerID, details, isBorrow);
}

// commandInputFromFile(string)
// reads and executes commands from command file
// Precondition: NONE
// Postcondition: all valid commands are executed
void Inventory::commandInputFromFile(const string filePath) {
    //create empty variables for storage
    string line;
    ifstream commandFile;

    //open the file
    commandFile.open(filePath);

    //get every line from the file
    while (getline(commandFile, line))
        //call the command function for every line
        command(line);

    //close the file
    commandFile.close();
}