// ---------------------------------media.cpp ------------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the Product media that
// stores all media types in a store and holds Genre BSTs that sorts movies. 
// Assumptions - None
// -----------------------------------------------------------------------------
#include "media.h"

// --------------------------------------------------------------------
// getGenre()
// parses list of genre BSTs to find the correct genre by its abbreviation
// Precondition: Media created correctly 
// Postcondition: returns address of genre if exists, null otherwise
Genre* Media::getGenre(const string abbrev)
{
    //iterate through all genres
    for(Genre * genre : genreList)
    {
        //check to see if the genre abbeiations are equal and return a pointer
        if(genre->getAbbreviation() == abbrev) {
            
            return genre;
        }
    }

    return nullptr;

}

// --------------------------------------------------------------------
// createGenre()
// set new Genre in map
// Precondition: Media created correctly 
// Postcondition: returns address of genre if exists, null otherwise
void Media::createGenre(const string command)
{

    //Look for the first comma that deliminates the abbreviation
    int abbreviationEnd = command.find(',');

    //Look for the second comma that deliminates the name
    int nameStart = abbreviationEnd+2;
    int nameEnd = command.find(',', nameStart);

    //Look for the parentheses that delminates how to parse the command string
    int parenthesesStart = command.find('(', nameEnd+1)+1;
    int parenthesesEnd = command.find(')', nameEnd);

    //Look for the brackets that delminates the key of the genre
    int bracketStart = command.find('[', parenthesesEnd+1)+1;
    int bracketEnd = command.find(']', parenthesesEnd);

    //store all the strings by substring the command
    string abbreviation = command.substr(0,abbreviationEnd);
    string name = command.substr(nameStart,nameEnd-nameStart);
    string parseString = command.substr(parenthesesStart,parenthesesEnd-parenthesesStart);
    string sortString = command.substr(bracketStart,bracketEnd-bracketStart);

    //search for the Genre
    if(getGenre(abbreviation) == nullptr)
    {
        //create a new Genre object
        Genre * g = new Genre(name, abbreviation, parseString, sortString);

        //add to the back of the list
        genreList.push_back(g);
    }
    else {
        cout << "Genre Abbreviation " << abbreviation << " already exists. " << endl;
    }

}

// --------------------------------------------------------------------
// printGenre()
// prints the entire Genre BST
// Precondition: Media created correctly 
// Postcondition: prints to the console the Genre BST
void Media::printGenres()
{
    //check to see if there are genres
    if (genreList.size() == 0)
    {
        cout << "No Genres available" << endl;
        return;
    }

    //iterate through all the genres and print
    for (Genre * g : genreList)
    {
        cout << *g;
    }
}