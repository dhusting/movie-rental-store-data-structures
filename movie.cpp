// ---------------------------------movie.cpp-----------------------------------
// Team Blockbuster - CS502A
// Created 20240310
// Modified 20240310
// -----------------------------------------------------------------------------
// Summary - This file contains the implementation for the Movie class
// Assumptions - Extends the NodeData class
// -----------------------------------------------------------------------------
#include <string>
#include <movie.h>
#include <vector>
#include "nodedata.h"

using namespace std;

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
string Movie::getType() {
    return "Movie";
};

// -----------------------------------------------------------------------------
// getDirector
// Getter for director property
// Precondition: Valid movie object
// Postcondition: Return string director value
string Movie::getDirector() {return director;}

// -----------------------------------------------------------------------------
// getMajorActor
// Getter for majorActor property
// Precondition: Valid movie object
// Postcondition: Return string majorActor value
string Movie::getMajorActor() {return majorActor;}