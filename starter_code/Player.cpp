#include "Player.h"

Player::Player(std::string playerName, Game* game)
    : playerName{ playerName }, game{ game }
{
    // Initialise points to 0
    points = 0;

    // Initialise patternLines and their lengths
    patternLines = new Tile**[PATTERN_LINE_ROWS];
    patternLineLengths = new int[PATTERN_LINE_ROWS];
    for (int i = 0; i < 5; i++){
        // Row 1 (index 0) has 1 max length, row 2 has 2 etc 
        patternLines[i] = new Tile*[i + 1];
        patternLineLengths[i] = 0;
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

Player::~Player(){
    // TODO
}

bool Player::addTilesToPatternLine(Tile** tiles, int tileCount, int patternLine){
    // TODO
}

void Player::addToFloorLine(Tile* tile){
    // TODO
}

bool Player::addTileToWall(int patternLine, int row, int column){
    // TODO  
}

bool Player::hasEndedGame(){
    // TODO
}

int Player::getCurrentScore(){
    // TODO
}

int Player::getFinalScore(){
    // TODO
}