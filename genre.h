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
        // Pointer to root node for tree traversal
        Node* root;
        // int vector matches serialized data to indexes of object fields 
        string parseFilters;
        // int vector matches sort fields to indexes of object fields
        string sortFilters;

        // -----------------------------------------------------------------------------
        // operator << overload
        // Print contents of Genre BST
        // Precondition: Valid Genre object
        // Postcondition: BST contents are printed to terminal output in order
        friend ostream &operator<<(ostream &out, const Genre &rhs);
        // Pseudocode:
        // Execute in order traversal of tree and print contents of each node

    public:
        // -----------------------------------------------------------------------------
        // Empty constructor
        // Initializes genre object with empty properties
        // Precondition: N/A
        // Postcondition: Genre object allocated and ready for use as BST
        Genre();
        // Pseudocode:
        // N/A

        // -----------------------------------------------------------------------------
        // Name, Abbreviation and Filter Constructor (name, abbreviation
        // , parseFilters, sortFilters)
        // Initializes genre object with unique parameters
        // Precondition: Abbreviation & filter parameters match valid file format
        // Postcondition: Genre object allocated and ready for use as BST
        Genre(string, string, string, string);
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
        // clear
        // Deallocate tree with rescursive, post-order traversal
        // Precondition: Pointer to current Node
        // Postcondition: All tree nodes deleted and memory freed
        void Genre::clear(Node* node) const;
        // Pseudocode:
        // Use recursive, post-order traversal to visit and delete each node

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
        // Postcondition: Return nodeData object if found, otherwise null
        bool find(string, NodeData&);
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

        // -----------------------------------------------------------------------------
        // print
        // Print contents of Genre BST
        // Precondition: Valid Genre object
        // Postcondition: BST contents are printed to terminal output recursively
        void print(ostream &out, Node* node);
        // Pseudocode:
        // Execute recursive in-order traversal of tree and print contents of each node
};