#include "inventory.h"

using namespace std;

int main() {

    Inventory i("Test", "1122 NE 12th St Philadelphia, PA 11223");

    i.commandInputFromFile("/home/dhusting/CSS502/Assignments/Assignment4/data4products.txt");

    return 0;
}