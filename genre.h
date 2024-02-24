#include "nodedata.h"
#include <vector>

using namespace std;

class Genre {

    private:
        string name;
        string abbreviation;
        struct Node {
            NodeData * data;
            Node * left;
            Node * right;
        };
        Node * head;
        vector<int> parsefilter;
        vector<int> sortfilter;
    public:

    Genre(string, string, int, int);
    ~Genre();

    bool insert(NodeData*);
    Node& find(string);

};