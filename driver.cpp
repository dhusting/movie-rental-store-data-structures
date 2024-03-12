#include "inventory.h"

using namespace std;

int main() {

    Inventory i("Test", "1122 NE 12th St Philadelphia, PA 11223");

    i.commandInputFromFile("/home/dhusting/CSS502/Assignments/Assignment4/data4products.txt");
    i.commandInputFromFile("/home/dhusting/CSS502/Assignments/Assignment4/data4genres.txt");
    i.commandInputFromFile("/home/dhusting/CSS502/Assignments/Assignment4/data4movies.txt");
    i.commandInputFromFile("/home/dhusting/CSS502/Assignments/Assignment4/data4customers.txt");
    i.commandInputFromFile("/home/dhusting/CSS502/Assignments/Assignment4/data4commands.txt");

    return 0;
}