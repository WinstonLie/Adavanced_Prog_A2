
#ifndef AZUL_PLAYER
#define AZUL_PLAYER

#include "Game.h"
#include <string>

class Player{
    public:
        Player(std::string playerName);
        ~Player();
        void addTilesToPatternLine(Tile** tiles, int tileCount, int patternLine);
        void addToFloorLine(Tile* tile);
        bool addTileToWall(int patternLine, int row, int column);
        bool hasEndedGame();
        int getCurrentScore();
        int getFinalScore();

    private:
        std::string playerName;
        Game* game;
        int points;
        Tile*** patternLines;
        Tile*** wall;
        Tile** floorLine;
        int floorLineCount;
};

#endif // AZUL_PLAYER