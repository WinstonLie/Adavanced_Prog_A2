
#ifndef AZUL_LINKEDLIST
#define AZUL_LINKEDLIST

#include "Node.h"
#include "Game.h"

class LinkedList{
    public:
        LinkedList();
        ~LinkedList();
        int getSize();
        void insertFront(Tile* tile);
        void insertBack(Tile* tile);
        void removeTiles(Tile* colour, Tile[]& tiles, int& tileCount);
        void remove(Tile* tile);
        void clear();

    private:
        Game* game;
        int size;
        Node* head;
};

#endif // AZUL_LINKEDLIST