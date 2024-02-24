#include <string>

using namespace std;

class NodeData{
    private:
        string id;
        string title;
        int stock;
        string releaseDate;
        int releaseYear;
        double lateFee;

    public:
        int getStock() {return stock;}
        void borrowStock() {stock-=1;}
        void returnStock() {stock+=1;}
};