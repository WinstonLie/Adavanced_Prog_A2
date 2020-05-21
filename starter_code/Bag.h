#ifndef AZUL_BAG
#define AZUL_BAG

#include <vector>
#include "Tile.h"


class Bag{
    public:

        // Default constructor, creates an empty bag
        Bag();

        // Copy constructor, copies tiles from otherBag to this bag
        Bag(std::vector<Tile*> otherBag);

        // Deconstructor, deletes all tiles in bag
        ~Bag();

        // Inserts a tile to the end of the bag
        void insertIntoBag(Tile* tile);

        // Removes a tile from the bag from the specific index
        // Does this by swapping index with last element then popping it off
        // Assumes that the index is within bounds  
        void removeFromBag(int index);

        // Returns the amount of tiles in the bag
        int getSize();

        // Returns the tile pointer at the specific index
        // Assumes that the index is within bounds  
        Tile* get(int index);
        
    private:

        // Vector that acts as the bag
        std::vector<Tile*> bag;
};

#endif //AZUL_BAG