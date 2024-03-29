// ---------------------------------genre.h ------------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240225
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the Genre class
// Assumptions - Filters for each genre will be provided from either config
// file or user
// -----------------------------------------------------------------------------
#ifndef GENRE_H
#define GENRE_H
#include "nodedata.h"
#include "movie.h"
#include <vector>

using namespace std;

// -----------------------------------------------------------------------------
// Genre Class
// Summary - Provides quick search of media inventory for each genre
class Genre {

    // -----------------------------------------------------------------------------
    // operator << overload
    // Print contents of Genre BST
    // Precondition: Valid Genre object
    // Postcondition: BST contents are printed to terminal output in order
    friend ostream &operator<<(ostream &out, const Genre &rhs);
    // Pseudocode:
    // Execute in order traversal of tree and print contents of each node

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
        string parseString;
        // int vector matches sort fields to indexes of object fields
        string sortString;
  
        // -----------------------------------------------------------------------------
        // print
        // Print contents of Genre BST
        // Precondition: Valid Genre object
        // Postcondition: BST contents are printed to terminal output recursively
        void print(ostream &out, Node* node) const;
        // Pseudocode:
        // Execute recursive in-order traversal of tree and print contents of each node

        // -----------------------------------------------------------------------------
        // split
        // Split string into substrings separated by char delimiter
        // Precondition: String input & char delimiter
        // Postcondition: Vector of substrings
        vector<string> split(string input, char delimiter) const;
        // Pseudocode:
        // dump input into stringstream buffer
        // use getline to read substrings from buffer

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
        string getName();
        // Pseudocode:
        // Return name value

        // -----------------------------------------------------------------------------
        // getAbbreviation
        // Getter for abbreviation property
        // Precondition: Valid genre object
        // Postcondition: Return string abbreviation value
        string getAbbreviation();
        // Pseudocode:
        // Return abbreviation value

        // -----------------------------------------------------------------------------
        // clear
        // Deallocate tree with rescursive, post-order traversal
        // Precondition: Pointer to current Node
        // Postcondition: All tree nodes deleted and memory freed
        void clear(Node* node) const;
        // Pseudocode:
        // Use recursive, post-order traversal to visit and delete each node

        // -----------------------------------------------------------------------------
        // insert
        // Method to insert data into the BST while maintaing sorted order
        // Precondition: String input to be parsed into movie object
        // Postcondition: Data inserted into ordered leaf of the tree
        bool insert(string);
        // Pseudocode:
        // Iterate down the tree using parameter as the comparison value.  Add new
        // leaf node with param NodeData value once nullptr node is reached

        // -----------------------------------------------------------------------------
        // find
        // Method to retrieve inventory data from BST to update or print
        // Precondition: Search key parameter
        // Postcondition: Return nodeData object if found, otherwise null
        bool find(string, NodeData*&);
        // Pseudocode:
        // Iterate down the tree using parameter as the comparison value.  Return
        // NodeData value if equal comparison, nullptr value if media doesn't exist

        // -----------------------------------------------------------------------------
        // setField
        // Assign parameter input to parameter field
        // Precondition: Input & field string parameters
        // Postcondition: Parameter field is assigned to parameter input
        void setField(Movie*, string, string);
        // Pseudocode:
        // Match field name to object field, assign input to field and convert to type

        // -----------------------------------------------------------------------------
        // buildSortField
        // Assign parameter input to parameter field
        // Precondition: Input & field string parameters
        // Postcondition: Parameter field is assigned to parameter input
        string buildSortField(Movie*, string, string);
        // Pseudocode:
        // Match field name to object field, assign input to field and convert to type

        // -----------------------------------------------------------------------------
        // buildMovie
        // Match input to fields w/ filter parameter
        // Precondition: Input & filter parameters
        // Postcondition: Return movie pointer with input data
        Movie* buildMovie(vector<string>, vector<string>);
        // Pseudocode:
        // Use filters to match input to movie fields

        // -----------------------------------------------------------------------------
        // print
        // Print contents of Genre BST
        // Precondition: Open output stream parameter
        // Postcondition: BST contents are printed to terminal output recursively
        void print(ostream &out) const;
        // Pseudocode:
        // Execute recursive in-order traversal of tree and print contents of each node
};

#endif