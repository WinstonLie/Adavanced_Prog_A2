
#ifndef AZUL_PLAYER
#define AZUL_PLAYER

#include "Tile.h"
#include "Game.h"
#include <vector>
#include <string>

// The width and length of the wall
#define WALL_DIMENSION 5

// A two dimensional array that shows the coloured background of the wall
// Used to determine where a colour goes in a wall
const Types WALL_COLOURS[WALL_DIMENSION][WALL_DIMENSION] =
                {{Dark_Blue, Yellow, Red, Black, Light_Blue},
                {Light_Blue, Dark_Blue, Yellow, Red, Black},
                {Black, Light_Blue, Dark_Blue, Yellow, Red},
                {Red, Black, Light_Blue, Dark_Blue, Yellow},
                {Yellow, Red, Black, Light_Blue, Dark_Blue}};

// The amount of rows for the pattern lines (rows on left)
#define PATTERN_LINE_ROWS 5

// The length of the floor line (line below pattern lines and wall)
#define FLOOR_LINE_LENGTH 7

// The amount of points to subtract for every element in the floor line
const int FLOOR_LINE_PENALTIES[] = {-1, -1, -2, -2, -2, -3, -3};

//Has the same dimension as walls
#define COLOUR_COUNT      5

// Directions to use when figuring out how many tiles a placed tile
// is connected to
#define DIRECTION_NORTH 0
#define DIRECTION_EAST 1
#define DIRECTION_SOUTH 2
#define DIRECTION_WEST 3

// Forward delcaration for game class
class Game;

// Class Player contains everything that relates to an individual player
// , including name, points, pattern lines, wall and floor line. ALso
// contains a reference to the game so they can directly add tiles to the lid.
class Player{
    public:
        
        // Constructs the player and initialises the structures
        Player(std::string playerName);

        // Loading constructor
        Player(std::string playerName, int points, Tile*** patternLine,
          int* patternLineRowCounts, Tile*** wall, Tile** floorLine,
          int floorLineCount);
        
        // Deconstructor for player
        // Deletes all tiles contained, doesn't delete Game
        ~Player();
        
        // Input is an array of tiles, and int of the
        //   length of array and index of pattern line row
        // Adds tile/s to the pattern line
        // Leftover tiles from this will be placed on floor line
        // If tile doesn't match the starting value, then return false
        // This method doesn't delete tiles, needs to be cleaned up afterwards
        bool addTilesToPatternLine(Tile** tiles, int tileCount, int patternLineRow);
        
        // Adds the tile to the floor line
        void addToFloorLine(Tile* tile);
        
        // Moves all tiles in full pattern rows to the wall.
        // All tiles except the first in the row for valid rows will be moved
        //   to floor line
        // Points earned from placing the tile will be added to total here
        // Also subtracts points due to floor line and clears it out
        // Returns true if they contained the first player marker in their floor line
        bool addTilesToWalls(std::vector<int>& rowsMoved, std::vector<int>& pointsEarned, int& pointSubtracted);

        // Checks to see if there is a completed row on the board
        // Returns true if completed row exists, else false
        bool hasEndedGame();
        
        // Returns current score of the player
        int getPoints();
        
        // Adds up end-game additional points to current score
        // Involves adding bonus points due to completed rows, columns and colours
        void updateEndGamePoints();

        //returns player name
        std::string getPlayerName();

        //get Wall data for saving
        std::string getWall();

        //get PatternLine data for saving
        std::string getPatternLine();

        //get floorLine data for saving
        std::string getFloorLine();

        //set game that the player is in
        // As player expects game to be set, seg faults will occur
        // if set to nullptr
        void setGame(Game* game);

        // Returns a string displaying the board, for use in console
        std::string displayMosaic();

        // Returns the penalty line for the player, for use in console
        std::string displayPenalty();

        // Returns true if tile can be placed into pattern line, else false
        bool canPlaceInPatternRow(Types colour, int patternRowIndex);

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
        int tilesInDirection(int row, int column, int direction);

        // Checks to see if the type of tile exists in the row
        // Returns true if present, else false
        bool tileInRowOfWall(Types colour, int row);
};

#endif // AZUL_PLAYER