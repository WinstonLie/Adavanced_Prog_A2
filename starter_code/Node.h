#ifndef AZUL_NODE
#define AZUL_NODE

#include "Tile.h"

// Class Node is used to store the tiles and next pointers for the
// CentreTable class.
class Node{

    public:
        // Constructor that creates a node that contains a tile
        Node(Tile* tile);

        // Deconstructor, doesn't delete the tile it contains if it
        // has one while being deleted
        ~Node();

        // Sets the next node pointer
        void setNext(Node* node);

        // Gets the next node pointer
        Node* getNext();

        // Gets the tile contained in this node
        Tile* getTileFromNode();
        
        // Sets the tile contained in this node
        void setTile(Tile* tile);

    private:
        
        // The tile that the node contains
        Tile* tile;

        // The next node in the linked list, or nullptr if none
        Node* nextNode;
};

#endif //AZUL_NODE