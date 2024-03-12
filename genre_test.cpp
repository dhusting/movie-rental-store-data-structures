// -------------------------------genre_test.cpp--------------------------------
// Team Blockbuster - CS502A
// Created 20240311
// Modified 20240311
// -----------------------------------------------------------------------------
// Summary - Test file
// Assumptions - N/A
// -----------------------------------------------------------------------------
//#include "inventory.h"
#include "genre.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/* int main() {
    // instantiate inventory
    Inventory inventory;
    inventory.commandInputFromFile("product&genre_format.txt");
    inventory.commandInputFromFile("data4movies.txt");
    inventory.commandInputFromFile("data4customers.txt");

    // run commands
    inventory.commandInputFromFile("data4commands.txt");

    // build genres
    Genre *classics = new Genre("C", "Classic", "Genre, Stock, Director"
        ", Title, MajorActor_ReleaseDate", "ReleaseDate, MajorActor");
    Genre *dramas = new Genre("D", "Drama", "Genre, Stock, Director"
        ", Title, ReleaseYear", "Director, Title");
    Genre *comedies = new Genre("F", "Comedy", "Genre, Stock, Director"
        ", Title, ReleaseYear", "Title, ReleaseYear");

    ifstream input;
    input.open("data4movies.txt");  // open stream

    // process movie file, sort movie objects into genre trees
    string line;
    while (getline(input, line)) {
        stringstream ss(line);
        vector<string> terms;
        while (ss.good()) {
            string sub;
            getline(ss, sub, ',');
            terms.push_back(sub);
        }
        if (terms[0] == "C")
            classics->insert(line);
        else if (terms[0] == "D")
            dramas->insert(line);
        else if (terms[0] == "F")
            comedies->insert(line);
    }

    input.close();    // close stream

    // print genres 
    cout << "classics: " << classics << endl;
    cout << "dramas: " << dramas << endl;
    cout << "comedies: " << comedies << endl;

    delete classics;
    delete dramas;
    delete comedies;

    return 0;   // test complete
} */