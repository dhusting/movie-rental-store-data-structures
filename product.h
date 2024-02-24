#include <string>

using namespace std;

class Product {

    private:
        //name of the product
        string name;

    public:
        // --------------------------------------------------------------------
        // Default Constructor
        // Precondition: NONE
        // Postcondition: Initialized Product with no name
        Product();

        // --------------------------------------------------------------------
        // Name Constructor
        // Precondition: NONE
        // Postcondition: Initialized Product with name
        Product(const string newName) {this->name = newName; }

        // --------------------------------------------------------------------
        // setName()
        // Precondition: Product must be initialized correctly
        // Postcondition: Product with new name
        void setName(const string newName) { this->name = newName; }

        // --------------------------------------------------------------------
        // getName()
        // Precondition: Product must be initialized correctly
        // Postcondition: name is returned
        string getName() { return this->name; }

};