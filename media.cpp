#include "media.h"

Genre* Media::getGenre(const string abbrev)
{

    for(Genre genre : genreList)
    {
        if(genre.getAbbreviation() == abbrev)
            return &genre;
    }

    return nullptr;

}

void Media::createGenre(const string command)
{

    int abbreviationEnd = command.find(',');
    int nameEnd = command.find(',', abbreviationEnd+2);

    int parenthesesStart = command.find('(', nameEnd+1)+1;
    int parenthesesEnd = command.find(')', nameEnd);

    int bracketStart = command.find('[', parenthesesEnd+1)+1;
    int bracketEnd = command.find(']', parenthesesEnd);

    string abbreviation = command.substr(0,abbreviationEnd);
    string name = command.substr(abbreviationEnd+1,nameEnd);
    string parseString = command.substr(parenthesesStart,parenthesesEnd);
    string sortString = command.substr(bracketStart,bracketEnd);

    if(getGenre(abbreviation) == nullptr)
    {
        Genre g(name, abbreviation, parseString, sortString);

        genreList.push_back(g);
    }
    else {
        
    }

}

void Media::printGenre()
{
    if (genreList.size() == 0)
    {
        cout << "No Genres available" << endl;
        return;
    }

    for (Genre g : genreList)
    {
        cout << g;
    }
}