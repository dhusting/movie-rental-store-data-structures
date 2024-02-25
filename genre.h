// ---------------------------------genre.h ------------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240225
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the Genre class
// Assumptions - Filters for each genre will be provided from either config
// file or user
// -----------------------------------------------------------------------------
#include "nodedata.h"
#include <vector>

using namespace std;

// -----------------------------------------------------------------------------
// Genre Class
// Summary - Provides quick search of media inventory for each genre
class Genre {

    private:
        // Genre name
        string name;
        // Char abbreviation for genre in file format
        string abbreviation;
        // BST tree node struct (binary node, contains pointer to NodeData)
        struct Node {
            NodeData* data;
            Node* left;
            Node* right;
        };
        // Pointer to head node for tree traversal
        Node* head;
        // int vector matches serialized data to indexes of object fields 
        vector<int> parseFilters;
        // int vector matches sort fields to indexes of object fields
        vector<int> sortFilters;

    public:
        // -----------------------------------------------------------------------------
        // Name, Abbreviation and Filter Constructor (name, abbreviation
        // , parseFilters, sortFilters)
        // Initializes genre object with unique parameters
        // Precondition: Abbreviation & filter parameters match valid file format
        // Postcondition: Genre object allocated and ready for use as BST
        Genre(string, string, vector<int>, vector<int>);
        // Pseudocode:
        // Assign genre properties to parameter values

        // -----------------------------------------------------------------------------
        // Destructor
        // Deallocates genre object
        // Precondition: Valid genre object
        // Postcondition: Memory used by genre object is freed
        ~Genre();
        // Pseudocode:
        // Post order traversal of BST, delete each node during visit

        // -----------------------------------------------------------------------------
        // getName
        // Getter for name property
        // Precondition: Valid genre object
        // Postcondition: Return string name value
        string getName() {return name;}
        // Pseudocode:
        // Return name value

        // -----------------------------------------------------------------------------
        // getAbbreviation
        // Getter for abbreviation property
        // Precondition: Valid genre object
        // Postcondition: Return string abbreviation value
        string getAbbreviation() {return abbreviation;}
        // Pseudocode:
        // Return abbreviation value

        // -----------------------------------------------------------------------------
        // insert
        // Method to insert data into the BST while maintaing sorted order
        // Precondition: Pointer to NodeData object to insert into tree
        // Postcondition: Data inserted into ordered leaf of the tree
        bool insert(NodeData*);
        // Pseudocode:
        // Iterate down the tree using parameter as the comparison value.  Add new
        // leaf node with param NodeData value once nullptr node is reached

        // -----------------------------------------------------------------------------
        // find
        // Method to retrieve inventory data from BST to update or print
        // Precondition: Search key parameter
        // Postcondition: Return reference to nodeData object if found, else nullptr
        NodeData& find(string);
        // Pseudocode:
        // Iterate down the tree using parameter as the comparison value.  Return
        // NodeData value if equal comparison, nullptr value if media doesn't exist

        // -----------------------------------------------------------------------------
        // setKey
        // Method to build NodeData key using sortFilter & matching data
        // Precondition: NodeData parameter
        // Postcondition: Set string concatenation of matching NodeData fields in
        // ID field
        void setKey(NodeData&);
        // Pseudocode:
        // Iterate through sortFilters, each filter represents an index of a getter
        // method in the NodeData object.  Execute methods and concatentate results
        // into a string key, then assign to NodeData id field
};