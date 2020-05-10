
#ifndef AZUL_PLAYER
#define AZUL_PLAYER

#include "Game.h"
#include <string>

#define WALL_DIMENSION 5
#define PATTERN_LINE_ROWS 5
#define FLOOR_LINE_LENGTH 7
class Player{
    public:
        Player(std::string playerName, Game* game);
        ~Player();
        void addTilesToPatternLine(Tile** tiles, int tileCount, int patternLine);
        void addToFloorLine(Tile* tile);
        bool addTileToWall(int patternLine, int row, int column);
        bool hasEndedGame();
        int getCurrentScore();
        int getFinalScore();

    private:
        // Name of the player
        std::string playerName;
        // Game that the player is a part of
        Game* game;
        // Points that the player has
        int points;
        // pattern lines (area to left of wall)
        // rows from top to bottom have lengths 1,2,3,4,5
        Tile*** patternLines;
        // 5x5 two-dimensional array
        Tile*** wall;
        // Array of length 7 at the bottom
        Tile** floorLine;
        // Amount of tiles in the floor line
        int floorLineCount;
};

#endif // AZUL_PLAYER