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