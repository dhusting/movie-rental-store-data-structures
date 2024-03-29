// --------------------------------nodeData.h ----------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240225
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the NodeData class
// Assumptions - The class is abstract and is meant be extended to allow for
// additional media type extensibility
// -----------------------------------------------------------------------------
#ifndef NODEDATA_H
#define NODEDATA_H
#include <string>
#include <iostream>
using namespace std;

// -----------------------------------------------------------------------------
// NodeData Class
// Summary - Defines generic media fields. The class is designed to be extended
// not implemented. The destructor is defined as a pure virtual function
// for simplest abstract behavior
class NodeData {

    // -----------------------------------------------------------------------------
    // operator << overload
    // Print contents of NodeData
    // Precondition: Valid NodeData object
    // Postcondition: NodeData contents printed to terminal output
    friend ostream& operator<<(ostream &out, const NodeData &rhs);
    // Pseudocode:
    // NodeData contents printed to terminal output

    private:
        // Id key used for comparrisons within BST implementation
        string id;
        // Media title
        string title;
        // Amount of copies available in the inventory
        int stock;
        // Date media released
        string releaseDate;
        // Media release year
        int releaseYear;
        // Accumulated late fees
        double lateFee;

    public:
        // -----------------------------------------------------------------------------
        // Empty constructor
        // Returns empty NodeData instance
        // Precondition: N/A
        // Postcondition: Empty NodeData object
        NodeData() {}

        // -----------------------------------------------------------------------------
        // Constructor
        // Allocates NodeData object, pure virtual implementation
        // Precondition: N/A
        // Postcondition: NodeData object allocated with parameter properties
        NodeData(string id, string title, int stock, string releaseDate
            , int releaseYear, double lateFee) {
                this->id = id;
                this->title = title;
                this->stock = stock;
                this->releaseDate = releaseDate;
                this->releaseYear = releaseYear;
                this->lateFee = lateFee;
        }
        // Pseudocode:
        // Assign parameters to properties
        
        // -----------------------------------------------------------------------------
        // Destructor
        // Deallocates NodeData object, pure virtual implementation
        // Precondition: Valid NodeData object
        // Postcondition: Memory used by NodeData object is freed
        ~NodeData() {}
        // Pseudocode:
        // Child object overloads destructor

        // -----------------------------------------------------------------------------
        // getType
        // Pure virtual function that returns media type
        // Precondition: N/A
        // Postcondition: Return string value of media type
        virtual string getType() const = 0;
        // Pseudocode:
        // Pure virtual implementation makes NodeData an abstract class

        // -----------------------------------------------------------------------------
        // operator == overload
        // Check two nodeData instances for equality
        // Precondition: Two nodeData parameters
        // Postcondition: Return true if parameters are equal, false otherwise
        bool operator==(const NodeData& rhs) const;

        // -----------------------------------------------------------------------------
        // operator > overload
        // Check if left operand is greater than the right
        // Precondition: Two nodeData parameters
        // Postcondition: Return true if left operand is greater, false otherwise
        bool operator>(const NodeData& rhs) const;

        // -----------------------------------------------------------------------------
        // getId
        // Getter for id property
        // Precondition: Valid NodeData object
        // Postcondition: Return string id value
        string getId() const {return id;}

        // -----------------------------------------------------------------------------
        // setId
        // Setter for id property
        // Precondition: Valid NodeData object, string parameter
        // Postcondition: Assign id field to parameter
        void setId(string id) {this->id = id;}

        // -----------------------------------------------------------------------------
        // getTitle
        // Getter for title property
        // Precondition: Valid NodeData object
        // Postcondition: Return string title value
        string getTitle() const {return title;}

        // -----------------------------------------------------------------------------
        // setTitle
        // Setter for title property
        // Precondition: Valid NodeData object, string parameter
        // Postcondition: Assign title field to parameter
        void setTitle(string title) {this->title = title;}

        // -----------------------------------------------------------------------------
        // getStock
        // Getter for stock property
        // Precondition: Valid NodeData object
        // Postcondition: Return integer stock value
        int getStock() const {return stock;}

        // -----------------------------------------------------------------------------
        // setStock
        // Setter for stock property
        // Precondition: Valid NodeData object, int parameter
        // Postcondition: Assign stock field to parameter
        void setStock(int stock) {this->stock = stock;}

        // -----------------------------------------------------------------------------
        // borrowStock
        // Decrements stock property
        // Precondition: Valid NodeData object
        // Postcondition: Stock property decremented by one
        bool borrowStock() {
            if (stock > 0) {
                stock-=1;
                return true;
            } else
                return false;
        }

        // -----------------------------------------------------------------------------
        // returnStock
        // Increments stock property
        // Precondition: Valid NodeData object
        // Postcondition: Stock property incremented by one
        void returnStock() {stock+=1;}

        // -----------------------------------------------------------------------------
        // getReleaseDate
        // Getter for releaseDate property
        // Precondition: Valid NodeData object
        // Postcondition: Return string releaseDate value
        string getReleaseDate() const {return releaseDate;}

        // -----------------------------------------------------------------------------
        // setReleaseData
        // Setter for releaseDate property
        // Precondition: Valid NodeData object, string parameter
        // Postcondition: Assign releaseDate field to parameter
        void setReleaseDate(string releaseDate) {this->releaseDate = releaseDate;}

        // -----------------------------------------------------------------------------
        // getReleaseYear
        // Getter for releaseYear property
        // Precondition: Valid NodeData object
        // Postcondition: Return integer releaseYear value
        int getReleaseYear() const {return releaseYear;}

        // -----------------------------------------------------------------------------
        // setReleaseYear
        // Setter for releaseYear property
        // Precondition: Valid NodeData object, int parameter
        // Postcondition: Assign releaseYear field to parameter
        void setReleaseYear(int releaseYear) {this->releaseYear = releaseYear;}

        // -----------------------------------------------------------------------------
        // getLateFee
        // Getter for lateFee property
        // Precondition: Valid NodeData object
        // Postcondition: Return double lateFee value
        double getLateFee() const {return lateFee;}

        // -----------------------------------------------------------------------------
        // setLateFee
        // Setter for lateFee property
        // Precondition: Valid NodeData object, double parameter
        // Postcondition: Assign lateFee field to parameter
        void setLateFee(int lateFee) {this->lateFee = lateFee;}
};

#endif