#include "product.h"
#include "genre.h"
#include <list>

using namespace std;

class Media : public Product {

    private:
        //list of heads for genre BSTs
        list<Genre> genreList;

    public:
        // --------------------------------------------------------------------
        // getGenre()
        // parses list of genre BSTs to find the correct genre by its abbreviation
        // Precondition: Media created correctly 
        // Postcondition: returns address of genre if exists, null otherwise
        Genre& getGenre(string);

        // --------------------------------------------------------------------
        // createGenre()
        // create a new Genre and add it to the list
        // Precondition: Media created correctly 
        // Postcondition: returns address of genre if exists, null otherwise
        void createGenre(string);

};