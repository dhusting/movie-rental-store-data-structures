// ---------------------------------movie.cpp-----------------------------------
// Team Blockbuster - CS502A
// Created 20240310
// Modified 20240310
// -----------------------------------------------------------------------------
// Summary - This file contains the implementation for the Movie class
// Assumptions - Extends the NodeData class
// -----------------------------------------------------------------------------
#include <string>
#include <vector>
#include "movie.h"
#include "nodedata.h"

using namespace std;

// -----------------------------------------------------------------------------
// Empty constructor ()
// Initializes empty movie object
// Precondition: N/A
// Postcondition: Movie object allocated and ready for lookup in BST
Movie::Movie() : NodeData() {}

// -----------------------------------------------------------------------------
// All Movie and NodeData field constructor (Id, title, stock, releaseDate
// , releaseYear, lateFee, director, majorActor, parseFilters, sortFilters)
// Initializes movie object with fields set to parameter values
// Precondition: NodeData & Movie parameters
// Postcondition: Movie object allocated and ready for lookup in BST
Movie::Movie(string ID, string title, int stock, string releaseDate
    , int releaseYear, double lateFee, string director, string majorActor) 
    : NodeData (ID, title, stock, releaseDate, releaseYear, lateFee) {
    this->director = director;
    this->majorActor = majorActor;
}
// Pseudocode:
// Assign object properties to parameter values

// -----------------------------------------------------------------------------
// getType
// Override function that returns media type
// Precondition: N/A
// Postcondition: Return string value of media type
string Movie::getType() const {
    return "Movie";
};

// -----------------------------------------------------------------------------
// getDirector
// Getter for director property
// Precondition: Valid movie object
// Postcondition: Return string director value
string Movie::getDirector() const {return director;}

// -----------------------------------------------------------------------------
// setDirector
// Setter for director property
// Precondition: Valid NodeData object, string parameter
// Postcondition: Assign director field to parameter
void Movie::setDirector(string director) {this->director = director;}

// -----------------------------------------------------------------------------
// getMajorActor
// Getter for majorActor property
// Precondition: Valid movie object
// Postcondition: Return string majorActor value
string Movie::getMajorActor() const {return majorActor;}

// -----------------------------------------------------------------------------
// setMajorActor
// Setter for majorActor property
// Precondition: Valid NodeData object, string parameter
// Postcondition: Assign majorActor field to parameter
void Movie::setMajorActor(string majorActor) {this->majorActor = majorActor;}

// -----------------------------------------------------------------------------
// operator == overload
// Check two nodeData instances for equality
// Precondition: Two nodeData parameters
// Postcondition: Return true if parameters are equal, false otherwise
bool Movie::operator==(const Movie& rhs) const {return this->getId() 
    == rhs.getId();}

// -----------------------------------------------------------------------------
// operator > overload
// Check if left operand is greater than the right
// Precondition: Two nodeData parameters
// Postcondition: Return true if left operand is greater, false otherwise
bool Movie::operator>(const Movie& rhs) const {return this->getId() 
    > rhs.getId();}