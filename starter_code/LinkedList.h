
#ifndef AZUL_LINKEDLIST
#define AZUL_LINKEDLIST

#include "Node.h"
#include <string>
#include "Game.h"
//LinkedList implementation for Centre Factory

#define ARRAY_MAX_SIZE    100

class Game;

class LinkedList{
    public:
        LinkedList();
        ~LinkedList();
        // Returns the size of the list
        int getSize();
        // Inserts tile to the front of the list
        void insert(Tile* tile);
        //Remove tiles of a colour from the center factory and puts the removed tiles into an array
        void removeTiles(Types colour, Tile** tiles, int& tileCount);
        // Removes all tiles from the list and puts them into the lid
        void clear();
        std::string getCenterTableDetails();
        //Get all tiles from center factory to display in console
        std::string getTilesFromCenterTable();

    private:
        // Removes tile nodeToDel from the list
        // Sets prevNodes next node to nodeToDels next node
        void removeNode(Node* prevNode, Node* nodeToDel);
        Game* game;
        int size;
        Node* head;
};

#endif // AZUL_LINKEDLIST