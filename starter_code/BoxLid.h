#ifndef AZUL_BOXLID
#define AZUL_BOXLID

#include <vector>
#include "Tile.h"


class BoxLid{
    public:

        // Default constructor, creates an empty boxlid
        BoxLid();

        // Copy constructor, copies tiles in boxLid to this boxlid
        BoxLid(std::vector<Tile*> boxLid);

        // Destructor, deletes all tiles in lid
        ~BoxLid();

        // Inserts the tile into the box lid
        void insertIntoBoxLid(Tile* tile);

        // Removes the tile at the index from the lid
        // Assumes that the index is within bounds
        void removeFromBoxLid(int index);

        // Returns the amount of tiles in the lid
        int getSize();

        // Removes the tile at the index from the lid
        // Assumes that the index is within bounds        
        Tile* get(int index);
    
    private:

        // Vector to act as the lid
        std::vector<Tile*> boxLid;
};

#endif //AZUL_BOXLID