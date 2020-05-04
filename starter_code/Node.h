#include "Tile.h"

class Node{
    public:
        Node(Tile tile);
        ~Node();
        void setNext(Node node);
        Node getNext();
        Tile getTileFromNode();
    private:
        Tile tile;
        Node* nextNode;
};