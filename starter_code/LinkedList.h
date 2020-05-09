
#ifndef AZUL_LINKEDLIST
#define AZUL_LINKEDLIST

#include "Node.h"
#include "Game.h"
//LinkedList implementation for Centre Factory
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

    private:
        // Removes tile nodeToDel from the list
        // Sets prevNodes next node to nodeToDels next node
        void removeTile(Tile* prevNode, Tile* nodeToDel);
        Game* game;
        int size;
        Node* head;
};

#endif // AZUL_LINKEDLIST