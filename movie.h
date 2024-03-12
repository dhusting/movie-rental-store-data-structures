// ----------------------------------movie.h -----------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240225
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the Movie class
// Assumptions - Extends the NodeData class
// -----------------------------------------------------------------------------
#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include "nodedata.h"

using namespace std;

// -----------------------------------------------------------------------------
// Movie Class
// Summary - Extends NodeData class with two movie - specific fields
class Movie : NodeData {

    friend ostream& operator<<(ostream &out, const Movie &rhs) {
        out << rhs.getId() << ", " << rhs.getTitle() << ", " 
            << to_string(rhs.getStock()) << ", " << rhs.getReleaseDate() 
            << ", " << to_string(rhs.getReleaseYear()) << ", " 
            << to_string(rhs.getLateFee()) << ", " << rhs.getDirector() << ", "
            << rhs.getMajorActor();
        return out;
    }

    private:
        // Name of director
        string director;
        // Name of major actor
        string majorActor;

    public:
        // -----------------------------------------------------------------------------
        // Empty constructor ()
        // Initializes empty movie object
        // Precondition: N/A
        // Postcondition: Movie object allocated and ready for lookup in BST
        Movie();
        // Pseudocode:
        // N/A
        
        // -----------------------------------------------------------------------------
        // All Movie and NodeData field constructor (Id, title, stock, releaseDate
        // , releaseYear, lateFee, director, majorActor, parseFilters, sortFilters)
        // Initializes movie object with fields set to parameter values
        // Precondition: NodeData & Movie parameters
        // Postcondition: Movie object allocated and ready for lookup in BST
        Movie(string, string, int, string, int, double, string, string);
        // Pseudocode:
        // Assign object properties to parameter values

        // -----------------------------------------------------------------------------
        // getType
        // Override function that returns media type
        // Precondition: N/A
        // Postcondition: Return string value of media type
        string getType() const;

        // -----------------------------------------------------------------------------
        // getDirector
        // Getter for director property
        // Precondition: Valid movie object
        // Postcondition: Return string director value
        string getDirector() const;

        // -----------------------------------------------------------------------------
        // setDirector
        // Setter for director property
        // Precondition: Valid NodeData object, string parameter
        // Postcondition: Assign director field to parameter
        void setDirector(string director);

        // -----------------------------------------------------------------------------
        // getMajorActor
        // Getter for majorActor property
        // Precondition: Valid movie object
        // Postcondition: Return string majorActor value
        string getMajorActor() const;

        // -----------------------------------------------------------------------------
        // setMajorActor
        // Setter for majorActor property
        // Precondition: Valid NodeData object, string parameter
        // Postcondition: Assign majorActor field to parameter
        void setMajorActor(string majorActor);

        // -----------------------------------------------------------------------------
        // operator == overload
        // Check two nodeData instances for equality
        // Precondition: Two movie parameters
        // Postcondition: Return true if parameters are equal, false otherwise
        bool operator==(const Movie& rhs) const;

        // -----------------------------------------------------------------------------
        // operator > overload
        // Check if left operand is greater than the right
        // Precondition: Two movie parameters
        // Postcondition: Return true if left operand is greater, false otherwise
        bool operator>(const Movie& rhs) const;
};

#endif