// ---------------------------------media.h ------------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the Product media that
// stores all media types in a store and holds Genre BSTs that sorts movies. 
// Assumptions - None
// -----------------------------------------------------------------------------
#include "product.h"
#include "genre.h"
#include <map>

using namespace std;

class Media : public Product {

    private:
        // Genre instances
        map<string, Genre> genres;

    public:
        // --------------------------------------------------------------------
        // getGenre()
        // parses list of genre BSTs to find the correct genre by its abbreviation
        // Precondition: Media created correctly 
        // Postcondition: returns address of genre if exists, null otherwise
        Genre* getGenre(string);

        // --------------------------------------------------------------------
        // setGenre()
        // set new Genre in map
        // Precondition: Media created correctly 
        // Postcondition: N/A
        void setGenre(Genre);

};