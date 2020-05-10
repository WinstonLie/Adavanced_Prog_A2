
#ifndef AZUL_GAME
#define AZUL_GAME

#include "Player.h"
#include "Tile.h"
#include "LinkedList.h"
#include <vector>

class Game{
    public:
        Game(Player** players, int playerCount);
        ~Game();
        void populateBag();
        void populateFactories();
        int getPlayerCount();
        Player* getPlayer(int index);
        void getTilesFromFactory(int factoryIndex, Tile* colour, int& tileAmount, Tile*& tiles);
        void getTilesFromCentre(Tile* colour, int& tileAmount, Tile*& tiles);
        bool isFirstPlayerMarkerTaken();
        void addToBoxLid(Tile* tile);
        std::vector<Tile*>* getBoxLid();


    private:
        int playerCount;
        Player** players;
        std::vector<Tile*> bag;
        int factoryCount;
        Tile*** factories;
        LinkedList centreTable;
        std::vector<Tile*> boxLid;
        bool firstPlayerMarker;
};
#endif // AZUL_GAME
