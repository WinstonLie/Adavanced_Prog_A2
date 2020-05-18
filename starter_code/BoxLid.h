#ifndef AZUL_BOXLID
#define AZUL_BOXLID

#include <vector>
#include "Tile.h"


class BoxLid{
    public:
        BoxLid();
        BoxLid(std::vector<Tile*> boxLid);
        ~BoxLid();
        void insertIntoBoxLid(Tile* tile);
        void removeFromBoxLid(int value);
        int getSize();
        Tile* get(int index);
    
    private:
        std::vector<Tile*> boxLid;
};

#endif //AZUL_BOXLID