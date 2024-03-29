// --------------------------------genre.cpp -----------------------------------
// Team Blockbuster - CS502A
// Created 20240228
// Modified 20240228
// -----------------------------------------------------------------------------
// Summary - This file contains the implementation for the Genre class
// Assumptions - Filters for each genre will be provided from either config
// file or user
// -----------------------------------------------------------------------------
#include "nodedata.h"
#include "genre.h"
#include "movie.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

// -----------------------------------------------------------------------------
// operator << overload
// Print contents of Genre BST
// Precondition: Valid Genre object
// Postcondition: BST contents are printed to terminal output in order
ostream &operator<<(ostream &out, const Genre &rhs) {
    rhs.print(out);
    return out;
}

// -----------------------------------------------------------------------------
// print
// Print contents of Genre BST
// Precondition: Valid Genre object
// Postcondition: BST contents are printed to terminal output recursively
void Genre::print(ostream &out, Node* node) const {
    //in order traversal & print node
    if (node != nullptr) {
        print(out, node->left);
        out << *((Movie *)node->data) << endl;
        print(out, node->right);
    }
}

// -----------------------------------------------------------------------------
// split
// Split string into substrings separated by char delimiter
// Precondition: String input & char delimiter
// Postcondition: Vector of substrings
vector<string> Genre::split(string input, char delimiter) const {
    stringstream ss(input);     // add to buffer
    vector<string> subs;
    while (ss.good()) {     // check buffer limit
        string sub;
        getline(ss, sub, delimiter);  // read substring split by delimiter
        if (sub.at(0) == ' ')    // remove leading space
            sub = sub.substr(1);
        subs.push_back(sub);
    }
    return subs;
}

// -----------------------------------------------------------------------------
// Empty constructor
// Initializes genre object with empty properties
// Precondition: N/A
// Postcondition: Genre object allocated and ready for use as BST
Genre::Genre() { root = nullptr; }    // set root to null

// -----------------------------------------------------------------------------
// Name, Abbreviation and Filter Constructor (name, abbreviation
// , parseFilters, sortFilters)
// Initializes genre object with unique parameters
// Precondition: Abbreviation & filter parameters match valid file format
// Postcondition: Genre object allocated and ready for use as BST
Genre::Genre(string nam, string abv, string pFlt, string sFlt) {
    // Assign genre properties to parameter values
    name = nam;
    abbreviation = abv;
    parseString = pFlt;
    sortString = sFlt;
    root = nullptr;
}

// -----------------------------------------------------------------------------
// Destructor
// Deallocates genre object
// Precondition: Valid genre object
// Postcondition: Memory used by genre object is freed
Genre::~Genre() {
    clear(root);    // execute clear function from root to delete entire tree
}

// -----------------------------------------------------------------------------
// getName 
// Getter for name property
// Precondition: Valid genre object
// Postcondition: Return string name value
string Genre::getName() {
    return name;
}

// -----------------------------------------------------------------------------
// getAbbreviation
// Getter for abbreviation property
// Precondition: Valid genre object
// Postcondition: Return string abbreviation value
string Genre::getAbbreviation() {
    return abbreviation;
}

// -----------------------------------------------------------------------------
// clear
// Deallocate tree with rescursive, post-order traversal
// Precondition: Pointer to current Node
// Postcondition: All tree nodes deleted and memory freed
void Genre::clear(Node* node) const {
    //post-order traversal & delete node
    if (node != nullptr) {
        clear(node->left);  // traverse left
        clear(node->right); // traverse right
        delete node->data;  // delete node data
        delete node;    // delete node
        node = nullptr; // assign to nullptr to prevent hanging ref
    }
}

// -----------------------------------------------------------------------------
// insert
// Method to insert data into the BST while maintaing sorted order
// Precondition: Pointer to NodeData object to insert into tree
// Postcondition: Data inserted into ordered leaf of the tree
bool Genre::insert(string line) {
    // split input string
    vector<string> input = split(line, ',');
    // split parse string
    vector<string> filters = split(parseString, ',');
    Movie *movie = buildMovie(input, filters);

    // allocate new node & assign data
    Node *node = new Node();
        node->data = (NodeData *)movie;
        node->left = nullptr;
        node->right = nullptr;

    // if root is nullptr, assign new node to root
    if (root == nullptr)
        root = node;
    else {
        // iterative traversal & insert node as leaf, in order
        Node *cur = root;
        for(;;) {
            if (*((Movie *)cur->data) == *movie) {  // check if data already exists in tree
                cur->data->setStock(cur->data->getStock() 
                    + ((NodeData *)movie)->getStock()); // combine stock
                delete movie;   // deallocate movie
                delete node;    // deallocate new node
                return false;   // return false, insert failed
            } else if (*((Movie *)cur->data) > *movie)  // check if key is before cur
                if (cur->left == nullptr) {     // check if empty left child
                    cur->left = node;   // insert node as left child
                    break;
                }
                else cur = cur->left;   // traverse to left child
            else
                if (cur->right == nullptr) {    // check if empty right child
                    cur->right = node;  // insert node as right child
                    break;
                }
                else cur = cur->right;  // traverse to right child
        }
    }
    return true;    // data inserted, return true
}

// -----------------------------------------------------------------------------
// find
// Method to retrieve inventory data from BST to update or print
// Precondition: Search key parameter
// Postcondition: Return reference to nodeData object if found, else nullptr
bool Genre::find(string key, NodeData *& result) {
    //iterative traversal, assign result to reference parameter if found
    Node* cur = root;
    while (cur != nullptr) {
        if (cur->data->getId() == key) {    // check if found
            result = cur->data;    // assign to result parameter
            return true;    // return true, find success
        } else if (cur->data->getId() > key)    // check if key is before cur
            cur = cur->left;    // traverse left
        else
            cur = cur->right;   // traverse right
    }
    return false;   // return false, find unsuccessfull
}

// -----------------------------------------------------------------------------
// setField
// Assign parameter input to parameter field
// Precondition: Input & field string parameters
// Postcondition: Parameter field is assigned to parameter input
void Genre::setField(Movie *movie, string field, string input) {
    if (field == "Title")
        ((NodeData *)movie)->setTitle(input);
    else if (field == "Stock")
        ((NodeData *)movie)->setStock(stoi(input));
    else if (field == "ReleaseDate")
        ((NodeData *)movie)->setReleaseDate(input);
    else if (field == "ReleaseYear")
        ((NodeData *)movie)->setReleaseYear(stoi(input));
    else if (field == "LateFee")
        ((NodeData *)movie)->setLateFee(stod(input));
    else if (field == "Director")
        movie->setDirector(input);
    else if (field == "MajorActor")
        movie->setMajorActor(input);
}

// -----------------------------------------------------------------------------
// buildSortField
// Assign parameter input to parameter field
// Precondition: Input & field string parameters
// Postcondition: Parameter field is assigned to parameter input
string Genre::buildSortField(Movie *movie, string field, string sortField) {
    string data;
    if (field == "Title")
        data = ((NodeData *)movie)->getTitle();
    else if (field == "Stock")
        data = to_string(((NodeData *)movie)->getStock());
    else if (field == "ReleaseDate")
        data = ((NodeData *)movie)->getReleaseDate();
    else if (field == "ReleaseYear")
        data = to_string(((NodeData *)movie)->getReleaseYear());
    else if (field == "LateFee")
        data = to_string(((NodeData *)movie)->getLateFee());
    else if (field == "Director")
        data = movie->getDirector();
    else if (field == "MajorActor")
        data = movie->getMajorActor();
    
    // concat new data w/ sortfield
    if (sortField != "")
        return sortField + " " + data;
    else
        return data;
}

// -----------------------------------------------------------------------------
// buildMovie
// Match input to fields w/ filter parameter
// Precondition: Input & filter parameters
// Postcondition: Return movie pointer with input data
Movie* Genre::buildMovie(vector<string> input, vector<string> filters) {
    // iterate through input terms & assign to movie fields
    Movie *movie = new Movie();

    input.erase(input.begin());

    for (int i = 0; i < filters.size(); i++) {
        string field = filters[i];
        string term = input[i];

        if(field.find('_') != std::string::npos){
            stringstream subs(field);
            vector<string> subFields;
            while (subs.good()) {
                string sub;
                getline(subs, sub, '_');
                subFields.push_back(sub);
            }
            stringstream ts(term);
            for (int i = 0; i < subFields.size(); i++) {
                string first, last; // subterms are combinations of substrings
                ts >> first >> last;    // need to read twice
                string subTerm = first + " " + last;
                setField(movie, subFields[i], subTerm);
            }
        } else
            setField(movie, field, term);
    }

    // split sort string
    vector<string> sortFields = split(sortString, ',');
    string sortField = "";
    for(int i = 0; i < sortFields.size(); i++)
        sortField = buildSortField(movie, sortFields[i], sortField);
    ((NodeData *)movie)->setId(sortField);

    return movie;   // return pointer to movie object
}

// -----------------------------------------------------------------------------
// print
// Print contents of Genre BST
// Precondition: Open output stream parameter
// Postcondition: BST contents are printed to terminal output recursively
void Genre::print(ostream &out) const {
    print(out, root);
}