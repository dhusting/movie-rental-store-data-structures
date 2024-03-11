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

Product* Inventory::getProduct(const string abbrev)
{

    for(Product product : productList)
    {
        if(product.getAbbreviation() == abbrev)
            return &product;
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
    if (filesystem::exists("backup.bak"))
        return true;

    return false;
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
    if (checkForBackupFiles())
    {
        string line;
        ifstream commandFile;
        commandFile.open("backup.bak");
        while (getline(commandFile, line))
            command(line);
        commandFile.close();
    }
}

// calls checkForBackupFiles() to verify there are files to ingest
// if true
// grab one file
// create a new Inventory object
// set the name and address from the file
// iterate until there are no products left to create
// iterate until there are no genres left to create
// iterate until all movies have been inserted
// return true if capable

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
    
    int firstComma = line.find(',');

    string command = line.substr(firstComma);

    bool commandSuccessFlag = false;

    // execute command
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
    else if (isdigit(term))
        commandSuccessFlag = createCustomer(line);
    else {
        commandSuccessFlag = createMovie(line);
    }

    if(commandSuccessFlag)
    {
        ofstream outputFile("backup.bak");

        if (outputFile.is_open())
        {
            outputFile << line << endl;
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

    vector<string> commandFields;

    stringstream ss(command);
    string word;
    string id;

    int spaceCount = 0;

    // Parse the string and grab each word up to the 4th space
    while (ss >> word && spaceCount < 3) {
        if (word == " ") {
            spaceCount++;
        } else {
            commandFields.push_back(word);
        }
    }

    while (ss >> id);

    int customerID = stoi(commandFields.at(0));
    Customer * customer = customers.get(customerID);

    if(customer != nullptr)
    {
        Product * product = getProduct(commandFields.at(1));

        if (product != nullptr)
        {
            if (Media * mediaPtr = dynamic_cast<Media *>(product))
            {
                Genre * genre = mediaPtr->getGenre(commandFields.at(2));

                if (genre != nullptr)
                {

                    NodeData& node;

                    genre->find(id, node);

                    node->borrowStock();

                    addTransaction(customerID, command, false);
                }

            }
        }
    }

}
// searches the given string for information on the product
// call getProduct() and if not nullptr
// gets from the given string the Genre abbreviation
// calls getGenre() and if not nullptr
// gets from the given string the movie identification details using the
// parsing infor from the Genre class gets the details.
// calls getMovie() and if not nullptr
// reduces the stock by 1
// creates new transaction by utilizing borrowTransaction()

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
    vector<string> commandFields;

    stringstream ss(command);
    string word;
    string id;

    int spaceCount = 0;

    // Parse the string and grab each word up to the 4th space
    while (ss >> word && spaceCount < 3) {
        if (word == " ") {
            spaceCount++;
        } else {
            commandFields.push_back(word);
        }
    }

    while (ss >> id);

    int customerID = stoi(commandFields.at(0));
    Customer * customer = customers.get(customerID);

    if(customer != nullptr)
    {
        Product * product = getProduct(commandFields.at(1));

        if (product != nullptr)
        {
            if (Media * mediaPtr = dynamic_cast<Media *>(product))
            {
                Genre * genre = mediaPtr->getGenre(commandFields.at(2));

                if (genre != nullptr)
                {

                    NodeData& node = new Movie();

                    genre->find(id, node);

                    node->returnStock();

                    addTransaction(customerID, command, true);
                }

            }
        }
    }
}

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

// -----------------------------------------------------------------------------
// displayInventory()
// Executes an Inventory (‘I’) command. Outputs the inventory to the 
// console 
// Precondition: Inventory is initialized
// Postcondition: outputs all inventory to the console in order and blank
// if there are no values
bool Inventory::displayInventory() {
    for (Product product : productList)
    {

        Product * productPtr = &product;

        if (Media * mediaPtr = dynamic_cast<Media *>(productPtr))
        {
            mediaPtr->printGenre();
        }
        
    }
}
// iterate through all products if they exist
// iterate through all genres if they exist
// iterate through all trees
// output movie information and their stock

// -----------------------------------------------------------------------------
// displayHistory()
// Executes a History (‘H’) command. Outputs the transaction log of a 
// customer to the console given a customer ID 
// Precondition: Empty string or valid customer id parameter
// Postcondition: If param string is empty, display transactions 
// for all customers.  Otherwise, display transactions for given id,
// blank if no transactions.
void Inventory::displayHistory(const string term) const {
    // scans customer ID from terms
    // scans through all customers for customer ID
    // given customer IDiterates through all the customer transactions 
    // output the transaction to the console.
 
    int customer_ID = stoi(term);
    Customer * temp = customers.get(customer_ID);
    list<Transaction> tempTransactions = (*temp).transactions;
    list<Transaction>::iterator it;
    // TODO: Table header and logic for checking if transactions exist
    for (it = tempTransactions.begin(); it != tempTransactions.end(); ++it){
        cout << it->transactionID << " "
             << it->borrowDate << " "
             << it->dueDate << " "
             << it->returnDate << " "
             << it->transactionDetail << endl;
    }
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

    stringstream ss(command);

    string parsedField;

    while (getline(ss, parsedField, ',')) {
        commandFields.push_back(parsedField);
    }

    if(getProduct(commandFields.at(0)) == nullptr)
    {
        if (commandFields.at(1) == "M")
        {
            Media m(commandFields.at(2), commandFields.at(3));

            productList.push_back(m);
        }
    }
}

// call getProduct() and if returns nullptr
// create new Product object
// set the name of the product
// add the product to the list

// -----------------------------------------------------------------------------
// createGenre()
// Creates a new Genre Binary Search Tree. (Comedy, Classic, Drama, Etc)
// Precondition: Inventory and Product are initialized correctly
// Postcondition: creates a new genre BST if no genre exists with the same name
bool Inventory::createGenre(const string command) {
    
    Product * product = getProduct(to_string(command.at(0)));
    
    if(product != nullptr)
    {

        if(Media * mediaPtr = dynamic_cast<Media *>(product))
        {
            string genreCommand = command.substr(3);        
            mediaPtr->createGenre(genreCommand);
        }    

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
    string cat;
    getline(ss, cat, ',');

    // get matching genre & insert input line
    Product *product = &Products[0];
    Media *media = (Media *)product;
    Genre *genre = media->getGenre(cat);
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
// createTransaction()
// Creates a new transaction in the HashTable. ID is created off of date
// customer ID and all other details.
// Precondition: Customer id, mediaKey, and isReturn parameters
// Postcondition: a new transaction transaction is created in the table
// if the customer exists
bool Inventory::addTransaction(int customerID, string details, bool isReturn) {
    // call getMovie() if address returned
    // call getCustomer() if customer returned
    // call borrowStock() if isReturn is false, otherwise returnStock()
    // create a transaction in the list
    // TODO: Handle isReturn
    Customer* temp = customers.get(customerID);
    if (temp != nullptr)  {
        if (!isReturn) {
            temp->transactions.push_front(
                Transaction{
                    "transactionID",
                    "borrowDate",
                    "dueDate",
                    "returnDate",
                    details,
                    }
                );
        }
    }
    return true; // TODO: return success
}

// commandInputFromFile(string)
// reads and executes commands from command file
// Precondition: NONE
// Postcondition: all valid commands are executed
void Inventory::commandInputFromFile(const string filePath) {
    string line;
    ifstream commandFile;
    commandFile.open(filePath);
    while (getline(commandFile, line))
        command(line);
    commandFile.close();
}