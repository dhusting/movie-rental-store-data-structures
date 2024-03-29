// ---------------------------------product.h ------------------------------------
// Team Blockbuster - CS502A
// Created 20240224
// Modified 20240224
// -----------------------------------------------------------------------------
// Summary - This file contains the specification for the Product class that
// stores all product types in a store. 
// Assumptions - None
// -----------------------------------------------------------------------------
#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

using namespace std;

class Product {

    private:
        //name of the product
        string name;
        string abbreviation;

    public:
        // --------------------------------------------------------------------
        // Name Constructor
        // Precondition: NONE
        // Postcondition: Initialized Product with name
        Product(const string newName, const string abbreviation) 
            {this->name = newName; this->abbreviation = abbreviation;}

        // --------------------------------------------------------------------
        // Destructor
        // Precondition: Product instance
        // Postcondition: Product memory freed
        virtual ~Product() {}

        // --------------------------------------------------------------------
        // getName()
        // Precondition: Product must be initialized correctly
        // Postcondition: name is returned
        string getName() { return this->name; }

        // --------------------------------------------------------------------
        // getAbbreviation()
        // Precondition: Product must be initialized correctly
        // Postcondition: name is returned
        string getAbbreviation() { return this->abbreviation; }

};

#endif