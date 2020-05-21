
#ifndef AZUL_LINKEDLIST
#define AZUL_LINKEDLIST

#include "Node.h"
#include <string>
#include <vector>

#define ARRAY_MAX_SIZE    100

//LinkedList implementation for Centre Factory
class CentreTable{
    public:
        // Default constructor, creates an empty linked list
        CentreTable();

        // Constructor for when loading, converts vector to linked list
        CentreTable(std::vector<Tile*> centreTable);

        // Deconstructor, deletes all nodes and the tiles they contain
        // Called when game is deleted
        ~CentreTable();

        // Returns the size of the list
        int getSize();

        // Inserts tile to the front of the list
        void insert(Tile* tile);

        // Remove tiles of a colour from the center factory and puts the removed
        // tiles into an array
        void removeTiles(Types colour, Tile**& tiles, int& tileCount);

        // Used to produce string for save file
        std::string getCenterTableDetails();

        //Get all tiles from center factory to display in console
        std::string getTilesFromCenterTable();

    private:
        // Removes tile nodeToDel from the list
        // Sets prevNodes next node to nodeToDels next node
        void removeNode(Node* prevNode, Node*& nodeToDel);

        // The head node of the linked list, is also the last
        // node added
        Node* head;
};

#endif // AZUL_LINKEDLIST