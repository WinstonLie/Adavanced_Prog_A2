
#ifndef AZUL_PLAYER
#define AZUL_PLAYER

#include "Game.h"
#include <string>

#define WALL_DIMENSION 5
#define PATTERN_LINE_ROWS 5
#define FLOOR_LINE_LENGTH 7
const int FLOOR_LINE_PENALTIES[] = {-1, -1, -2, -2, -2, -3, -3};

class Player{
    public:
        
        // Constructs the player and initialises the structures
        Player(std::string playerName, Game* game);
        
        // Deconstructor for player
        ~Player();
        
        // Input is an array of tiles, and int of the
        //   length of array and index of pattern line row
        // Adds tile/s to the pattern line
        // Leftover tiles from this will be placed on floor line
        // If tile doesn't match the starting value, then return false
        bool addTilesToPatternLine(Tile** tiles, int tileCount, int patternLineRow);
        
        // Adds the tile to the floor line
        void addToFloorLine(Tile* tile);
        
        // Adds a tile from the pattern line to the wall.
        // All tiles except first will be moved to floor line
        // Points earned from placing the tile will be added to total here
        // Returns false if place on wall is already occupied or if pattern line is not full
        bool addTileToWall(int patternLineRow, int row, int column);

        // Checks to see if there is a completed row on the board
        bool hasEndedGame();
        
        // Returns current score of the player
        int getCurrentScore();
        
        // Adds up end-game additional points to current score and
        // returns result
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
        
        // Counts the amount of tiles in each row
        int* patternLineRowCounts;
        
        // 5x5 two-dimensional array
        Tile*** wall;
        
        // Array of length 7 at the bottom
        Tile** floorLine;
        
        // Amount of tiles in the floor line
        int floorLineCount;

        // Counts the amount of tiles in a specified direction in the wall from
        //   the coordinates given. Directions for numbers 0,1,2,3 are north, east,
        //   south, west. Return value is amount of tiles found in direction, or 0
        //   if direction is not within expected range.
        int Player::tilesInDirection(int row, int column, int direction);
};

#endif // AZUL_PLAYER