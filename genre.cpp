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
#include <vector>
#include <iostream>

using namespace std;

// -----------------------------------------------------------------------------
// operator << overload
// Print contents of Genre BST
// Precondition: Valid Genre object
// Postcondition: BST contents are printed to terminal output in order
ostream &operator<<(ostream &out, const Genre &rhs) {

}

// -----------------------------------------------------------------------------
// Empty constructor
// Initializes genre object with empty properties
// Precondition: N/A
// Postcondition: Genre object allocated and ready for use as BST
Genre::Genre() {}

// -----------------------------------------------------------------------------
// Name, Abbreviation and Filter Constructor (name, abbreviation
// , parseFilters, sortFilters)
// Initializes genre object with unique parameters
// Precondition: Abbreviation & filter parameters match valid file format
// Postcondition: Genre object allocated and ready for use as BST
Genre::Genre(string name, string abv, string pFlt
, string sFlt) {
    // Assign genre properties to parameter values
    name = name;
    abbreviation = abv;
    parseFilters = pFlt;
    sortFilters = sFlt;
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
bool Genre::insert(NodeData* data) {
    // allocate new node & assign data
    Node *node = new Node();
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;

    // if root is nullptr, assign new node to root
    if (root == nullptr)
        root = node;
    else {
        // iterative traversal & insert node as leaf, in order
        Node *cur = root;
        for(;;) {
            if (*cur->data == *data) {  // check if data already exists in tree
                delete node;    // deallocate new node
                return false;   // return false, insert failed
            } else if (*cur->data > *data)  // check if key is before cur
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
bool Genre::find(string key, NodeData& result) {
    //iterative traversal, assign result to reference parameter if found
    Node* cur = root;
    while (cur != nullptr) {
        if (cur->data->getId() == key) {    // check if found
            result = *cur->data;    // assign to result parameter
            return true;    // return true, find success
        } else if (cur->data->getId() > key)    // check if key is before cur
            cur = cur->left;    // traverse left
        else
            cur = cur->right;   // traverse right
    }
    return false;   // return false, find unsuccessfull
}

// -----------------------------------------------------------------------------
// setKey
// Method to build NodeData key using sortFilter & matching data
// Precondition: NodeData parameter
// Postcondition: Set string concatenation of matching NodeData fields in
// ID field
void Genre::setKey(NodeData&) {}
// Pseudocode:
// Iterate through sortFilters, each filter represents an index of a getter
// method in the NodeData object.  Execute methods and concatentate results
// into a string key, then assign to NodeData id field

// -----------------------------------------------------------------------------
// print
// Print contents of Genre BST
// Precondition: Valid Genre object
// Postcondition: BST contents are printed to terminal output recursively
void Genre::print(ostream &out, Node* node) {
    //in order traversal & print node
    if (node != nullptr) {
        print(out, node->left);
        out << *node->data << endl;
        print(out, node->right);
    }
}