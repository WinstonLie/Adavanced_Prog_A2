#include "Player.h"

Player::Player(std::string playerName, Game* game)
    : playerName{ playerName }, game{ game }
{
    // Initialise points to 0
    points = 0;

    // Initialise patternLines and their lengths
    patternLines = new Tile**[PATTERN_LINE_ROWS];
    patternLineRowCounts = new int[PATTERN_LINE_ROWS];
    for (int i = 0; i < 5; i++){
        // Row 1 (index 0) has 1 max length, row 2 has 2 etc
        // Pattern lines not set to nullptr as o 
        patternLines[i] = new Tile*[i + 1];
        patternLineRowCounts[i] = 0;
    }

    // Initialise wall
    wall = new Tile**[WALL_DIMENSION];
    for (int i = 0; i < WALL_DIMENSION; i++){
        wall[i] = new Tile*[WALL_DIMENSION];
        // Sets all spots in wall to nullptr
        for (int r = 0; r < WALL_DIMENSION; i++){
            wall[i][r] = nullptr;
        }
    }

    // Initialise floor line
    floorLine = new Tile*[FLOOR_LINE_LENGTH];

    // Initialise floor line count
    floorLineCount = 0;
}

Player::~Player(){
    // TODO
}

bool Player::addTilesToPatternLine(Tile** tiles, int tileCount, int patternLineRow){
    // Value to be output
    bool successfulTileAdd = false;
    // Check that patternLine is valid
    if (patternLineRow >= 0 && patternLineRow < PATTERN_LINE_ROWS){
        // Checks to see if either row is empty or first tile matches inserted ones
        if (patternLineRowCounts[patternLineRow] == 0 ||
          patternLines[patternLineRow][0]->getType() == tiles[0]->getType()){
            // Counts how many tiles have been input
            int inputTileCounter = 0;
            // counter for pattern line
            int* patternLineCounter = &patternLineRowCounts[patternLineRow];
            // While there are tiles to input, insert into pattern line
            while (*patternLineCounter < patternLineRow + 1 && inputTileCounter < tileCount){
                patternLines[patternLineRow][*patternLineCounter] = tiles[inputTileCounter];
                inputTileCounter++;
                *patternLineCounter++;
            }

            // If there are tiles left over, insert into floor line
            while (inputTileCounter < tileCount){
                addToFloorLine(tiles[inputTileCounter]);
                inputTileCounter++;
            }

            // Sets output value to true
            successfulTileAdd = true;
        }
    }

    // Returns true if operation was valid, otherwise false
    return successfulTileAdd;
}

void Player::addToFloorLine(Tile* tile){
    // Checks to see if floor line has space left
    if (floorLineCount < FLOOR_LINE_LENGTH){
        // If room left, then add tile to floor line
        floorLine[floorLineCount - 1] = tile;
        floorLineCount++;
    } else {
        // If no room left, send tile to game to put inside lid
        game->addToBoxLid(tile);
    }
}

bool Player::addTileToWall(int patternLineRow, int row, int column){
    // Value to be returned
    bool successfulAddToWall = false;
    // Checks that wall is empty and that pattern line row is full
    if (wall[row][column] != nullptr && patternLineRowCounts[patternLineRow] == patternLineRow + 1){
        // Places first tile from patternLine into wall
        wall[row][column] = patternLines[patternLineRow][0];
        // Removes tile pointer from patternLines
        patternLines[patternLineRow][0] = nullptr;
        // Puts all other tiles in row (if any exist) into lid
        for (int i = 1; i < patternLineRowCounts[patternLineRow]; i++){
            game->addToBoxLid(patternLines[patternLineRow][i]);
            patternLines[patternLineRow][i] = nullptr;
        }

        // Calculate points for new tile placement and add to points
        // TODO

        // Sets output to true
        successfulAddToWall = true;
    }

    // Returns output value
    return successfulAddToWall;
}

bool Player::hasEndedGame(){
    // Counter for rows
    int rowCount = 0;
    // Counter for columns
    int columnCount = 0;
    // Output value
    bool endedGame = false;
    // Loops through each row in wall
    while (endedGame == false && rowCount < WALL_DIMENSION){
        // Checks to see if value at spot is nullptr
        if (wall[rowCount][columnCount] == nullptr){
            // Move on to next row
            rowCount++;
        // If last column of row has been reached without finding a nullptr, then set
        // output to true
        } else if (columnCount == WALL_DIMENSION - 1){
            endedGame = true;
        // Else move on to the next column of same row
        } else {
            columnCount++;
        }
    }

    //Returns output
    return endedGame;
}

int Player::getCurrentScore(){
    return points;
}

int Player::getFinalScore(){
    // TODO
}