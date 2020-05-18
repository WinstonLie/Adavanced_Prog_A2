#ifndef AZUL_BAG
#define AZUL_BAG

#include <vector>
#include "Tile.h"


class Bag{
    public:
        Bag();
        Bag(std::vector<Tile*> otherBag);
        ~Bag();
        void insertIntoBag(Tile* tile);
        void removeFromBag(int value);
        int getSize();
        Tile* get(int index);
        
    
    private:
        std::vector<Tile*> bag;
};

#endif //AZUL_BAG