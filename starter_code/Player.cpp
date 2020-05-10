#include "Player.h"

Player::Player(std::string playerName, Game* game)
    : playerName{ playerName }, game{ game }
{
    // Initialise points to 0
    points = 0;

    // Initialise patternLines
    patternLines = new Tile**[PATTERN_LINE_ROWS];
    for (int i = 0; i < 5; i++){
        // Row 1 (index 0) has 1, row 2 has 2 etc 
        patternLines[i] = new Tile*[i + 1];
    }

    // Initialise wall
    wall = new Tile**[WALL_DIMENSION];
    for (int i = 0; i < WALL_DIMENSION; i++){
        wall[i] = new Tile*[WALL_DIMENSION];
    }

    // Initialise floor line
    floorLine = new Tile*[FLOOR_LINE_LENGTH];

    // Initialise floor line count
    floorLineCount = 0;
}