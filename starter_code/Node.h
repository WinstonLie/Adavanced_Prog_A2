#ifndef AZUL_NODE
#define AZUL_NODE

#include "Tile.h"

class Node{
    public:
        Node(Tile* tile);
        ~Node();
        void setNext(Node* node);
        Node* getNext();
        Tile* getTileFromNode();
        void setTile(Tile* tile);
    private:
        Tile* tile;
        Node* nextNode;
};

#endif //AZUL_NODE