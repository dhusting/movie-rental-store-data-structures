#include "inventory.h"

using namespace std;

int main() {

    Inventory i("Test", "1122 NE 12th St Philadelphia, PA 11223");

    i.commandInputFromFile("data4products.txt");
    i.commandInputFromFile("data4genres.txt");
    i.commandInputFromFile("data4movies.txt");
    i.commandInputFromFile("data4customers.txt");
    i.commandInputFromFile("data4commands.txt");

    return 0;
}