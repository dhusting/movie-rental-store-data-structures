// ---------------------------------media.h ------------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the Product media that
// stores all media types in a store and holds Genre BSTs that sorts movies. 
// Assumptions - None
// -----------------------------------------------------------------------------
#ifndef MEDIA_H
#define MEDIA_H
#include <list>
#include <iostream>
#include "product.h"
#include "genre.h"

using namespace std;

class Media : public Product {

    private:
        // Genre instances
        list<Genre> genreList;

    public:
    
        // --------------------------------------------------------------------
        // Constructor()
        // creates a media object by calling the constructor of it's parent class
        // Precondition: None
        // Postcondition: creates a new Media object
        Media(const string abbreviation, const string name): 
            Product(name, abbreviation) {};

        // --------------------------------------------------------------------
        // ~Media
        // Destructor - deallocates media instance
        // Precondition: Media instance
        // Postcondition: Media memory freed
        ~Media() {};

        // --------------------------------------------------------------------
        // getGenre()
        // parses list of genre BSTs to find the correct genre by its abbreviation
        // Precondition: Media created correctly 
        // Postcondition: returns address of genre if exists, null otherwise
        Genre* getGenre(const string);

        // --------------------------------------------------------------------
        // setGenre()
        // set new Genre in map
        // Precondition: Media created correctly 
        // Postcondition: returns address of genre if exists, null otherwise
        void createGenre(const string);

        // --------------------------------------------------------------------
        // printGenre()
        // prints the entire Genre BST
        // Precondition: Media created correctly 
        // Postcondition: prints to the console the Genre BST
        void printGenres();
};

#endif