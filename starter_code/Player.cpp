#include "Player.h"

Player::Player(std::string playerName, Game* game)
    : playerName{ playerName }, game{ game }
{
    // Initialise points to 0
    points = 0;

    // Initialise patternLines and their lengths
    patternLines = new Tile**[PATTERN_LINE_ROWS];
    patternLineRowCounts = new int[PATTERN_LINE_ROWS];
    for (int i = 0; i < PATTERN_LINE_ROWS; i++){
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
    // Checks that wall is empty and that pattern line row is full and that colour matches wall
    if (wall[row][column] != nullptr && patternLineRowCounts[patternLineRow] == patternLineRow + 1
      && patternLines[patternLineRow][0]->getType() == WALL_COLOURS[row][column]){
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
        // Count concurrent tiles in all directions of tile
        // Count horizontal (tiles to left and right)
        int horizontalTiles = tilesInDirection(row, column, 1) + tilesInDirection(row, column, 3);
        // Count vertical (tiles above and below)
        int verticalTiles = tilesInDirection(row, column, 0) + tilesInDirection(row, column, 2);
        // If no adjacent tiles, add one point
        if (horizontalTiles == 0 && verticalTiles == 0){
            points += 1;
        // If adjacent tiles found, then 
        } else {
            // If there are horizontal tiles, add amount of tiles plus the one that was just placed
            if (horizontalTiles != 0){
                points += horizontalTiles + 1;
            }
            
            // If there are vertical tiles, add amount of tiles plus the one that was just placed
            if (verticalTiles != 0){
                points += verticalTiles + 1;
            }
        }

        // Subtracts floor line values and empties tiles into lid
        // Also clears floor line
        for (int i = 0; i < floorLineCount; i++){
            points += FLOOR_LINE_PENALTIES[i];
            // starting player tile doesn't go back into lid, gets deleted and re-created
            if (floorLine[i]->getType() != starter_player){
                game->addToBoxLid(floorLine[i]);
            } else {
                delete floorLine[i];
            }
            floorLine[i] = nullptr;
        }
        floorLineCount = 0;

        // Sets output to true
        successfulAddToWall = true;
    }

    // Returns output value
    return successfulAddToWall;
}

int Player::tilesInDirection(int row, int column, int direction){
    // Tiles found in specified direction, will be returned
    int tileCount = 0;
    // Checks to see if direction is valid
    if (direction >= 0 && direction <= 3){
        // Initialises incremend and end points for values
        // increments are added every loop, when current row/column equals end
            // point, then end looping
        // End point of -2 means it will never be reached, used for unchanging axis
        int xIncrement;
        int yIncrement;
        int xEndPoint;
        int yEndPoint;
        // Sets increment/endpoint values according to direction
        // Directions for 0,1,2,3 are north,east,south,west
        if (direction == 0){
            xIncrement = 0;
            yIncrement = -1;
            xEndPoint = -2;
            yEndPoint = -1;
        } else if (direction == 1){
            xIncrement = 1;
            yIncrement = 0;
            xEndPoint = WALL_DIMENSION + 1;
            yEndPoint = -2;
        } else if (direction == 2){
            xIncrement = 0;
            yIncrement = 1;
            xEndPoint = -2;
            yEndPoint = WALL_DIMENSION + 1;
        } else if (direction == 3){
            xIncrement = -1;
            yIncrement = 0;
            xEndPoint = -1;
            yEndPoint = -2;
        }

        // Current row and column of loop
        int currentRow = row;
        int currentColumn = column;
        bool endOfDirection = false;
        // While the end of wall hasn't been found
        while (endOfDirection == false){
            // Increment the row and column by pre-defined amount
            currentRow += yIncrement;
            currentColumn += xIncrement;
            // Checks that rows and columns aren't at end point and that
            // spot in wall isn't empty
            if (currentRow != yEndPoint && currentColumn != xEndPoint
              && wall[currentRow][currentColumn] != nullptr){
                  tileCount++;
            // End of direction has been reached, end loop
            } else {
                endOfDirection = true;
            }
        }
    }

    // Return amount of tiles found
    return tileCount;
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

int Player::getPoints(){
    return points;
}

void Player::updateFinalPoints(){
    // Check for completed rows and columns
    for (int i = 0; i < WALL_DIMENSION; i++){
        // Check for completed rows
        if (tilesInDirection(i, -1, 1) == WALL_DIMENSION){
            points += 2;
        }
        // Check for completed columns
        if (tilesInDirection(-1, i, 2) == WALL_DIMENSION){
            points += 7;
        }
    }

    // Get counts for every colour (assumes same amount of colours as dimension of wall)
    int colourCount = WALL_DIMENSION;
    int maxCount = WALL_DIMENSION;
    int counts[colourCount];
    Types colours[colourCount] = {Dark_Blue, Yellow, Red, Black, Light_Blue};
    // Go through every row and column of wall
    for (int i = 0; i < WALL_DIMENSION; i++){
        for (int r = 0; r < WALL_DIMENSION; r++){
            // If there is a tile then add to the count of that tiles colour
            if (wall[i][r] != nullptr){
                for (int w = 0; w < colourCount; w++){
                    if (wall[i][r]->getType() == colours[w]){
                        counts[w]++;
                    }
                }
            }
        }
    }

    // Go through every colour count and if it is max, add points
    for (int i = 0; i < colourCount; i++){
        if (counts[i] == maxCount){
            points += 10;
        }
    }
}

std::string Player::getPlayerName(){
    return this->playerName;
}

std::string Player::getWall(){
    std::string data = "";

    for(int i = 0; i < WALL_DIMENSION; i++){
        for(int j = 0; j < WALL_DIMENSION; j++){
            data += wall[i][j]->getType();
        }
        data += "$\n";
    }
    data += '$';

    return data;
}

std::string Player::getPatternLine(){
    std::string data = "";

    for(int i = 0; i < PATTERN_LINE_ROWS ; i++){
        for(int j = 0 ; j < i+1 ; j++){
            data += patternLines[i][j]->getType();
        }
        data += "$\n";
    }
    data += "$";

    return data;
}

std::string Player::getFloorLine(){
    std::string data = "";

    for(int i = 0; i < FLOOR_LINE_LENGTH; i++){
        data += floorLine[i]->getType();
    }
    data += "$";

    return data;
}