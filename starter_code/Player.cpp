#include "Player.h"
#include <iostream>

Player::Player(std::string playerName)
    : playerName{ playerName }
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
        // Sets all pointers to nullptr
        for (int r = 0; r < i + 1; r++){
            patternLines[i][r] = nullptr;
        }
        // Sets the amount of tiles in row to 0
        patternLineRowCounts[i] = 0;
    }

    // Initialise wall
    wall = new Tile**[WALL_DIMENSION];
    for (int i = 0; i < WALL_DIMENSION; i++){

        wall[i] = new Tile*[WALL_DIMENSION];
        // Sets all spots in wall to nullptr
        for (int r = 0; r < WALL_DIMENSION; r++){
            wall[i][r] = nullptr;
        }
    }

    // Initialise floor line
    floorLine = new Tile*[FLOOR_LINE_LENGTH];
    for (int i = 0; i < FLOOR_LINE_LENGTH; i++){
        floorLine[i] = nullptr;
    }

    // Initialise floor line count
    floorLineCount = 0;
}

Player::Player(std::string playerName, int points, Tile*** patternLine,
          int* patternLineRowCounts, Tile*** wall, Tile** floorLine, int floorLineCount) :
          playerName{ playerName }, points{ points }, patternLines{ patternLine },
          patternLineRowCounts{ patternLineRowCounts }, wall{ wall }, floorLine{ floorLine },
          floorLineCount{ floorLineCount } {}

Player::~Player(){
    // Doesn't delete game as it is not owned by player

    //delete patternLines [Produces Segmentation Fault]
    for(int i = 0; i < PATTERN_LINE_ROWS ; i++){

        for(int r = 0; r < patternLineRowCounts[i] ; i++){

            delete patternLines[i][r];
            patternLines[i][r] = nullptr;
        }
    }

    //delete floorline
    for(int i = 0 ; i < FLOOR_LINE_LENGTH ; i++){

        delete floorLine[i];
        floorLine[i] = nullptr;
    }

    //delete wall
    for(int i = 0 ; i < WALL_DIMENSION ; i++){

        for ( int j = 0 ;  j < WALL_DIMENSION ; j++){

            delete wall[i][j];
            wall[i][j] = nullptr;
        }
    }

    //delete counts
    delete patternLineRowCounts;
    patternLineRowCounts = nullptr;

    //set game of this player to nullptr
    this->setGame(nullptr);

}

bool Player::addTilesToPatternLine(Tile** tiles, int tileCount, int patternLineRow){
    // Value to be output
    bool successfulTileAdd = false;
    // Check that patternLine is valid
    if (patternLineRow >= 0 && patternLineRow < PATTERN_LINE_ROWS){

        // Checks to see if either row is empty or first tile matches inserted one inside row
            if (patternLineRowCounts[patternLineRow] == 0 ||
              patternLines[patternLineRow][0]->getType() == tiles[0]->getType()){
                // Counts how many tiles have been input
                int inputTileCounter = 0;

                // counter for pattern line
                // While there are tiles to input, insert into pattern line
                while (patternLineRowCounts[patternLineRow] < patternLineRow + 1 && inputTileCounter < tileCount){

                    patternLines[patternLineRow][patternLineRowCounts[patternLineRow]] = tiles[inputTileCounter];
                    inputTileCounter++;
                    patternLineRowCounts[patternLineRow]++;
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
        floorLine[floorLineCount] = tile;
        floorLineCount++;
    } else {
        // If no room left, send tile to game to put inside lid
        game->addToBoxLid(tile);
    }
}

bool Player::addTilesToWalls(std::vector<int>& rowsMoved, std::vector<int>& pointsEarned, int& pointSubtracted){
    // Value to be returned
    bool isFirstPlayer = false;
    for (int i = 0; i < PATTERN_LINE_ROWS; i++){

        // Checks that wall is empty and that pattern line row is full and that colour matches wall
        if (patternLineRowCounts[i] == i + 1){
            int row = i;
            int column = -1;

            for (int r = 0; r < WALL_DIMENSION; r++){

                if (WALL_COLOURS[i][r] == patternLines[i][0]->getType()){
                    column = r;
                } else if (patternLines[i][0] == nullptr){
                }
            }

            // Places first tile from patternLine into wall
            wall[row][column] = patternLines[i][0];
            // Removes tile pointer from patternLines
            patternLines[i][0] = nullptr;

            // Puts all other tiles in row (if any exist) into lid
            for (int r = 1; r < patternLineRowCounts[i]; r++){
                game->addToBoxLid(patternLines[i][r]);
                patternLines[i][r] = nullptr;
            }

            //Resets counter for number of tiles in this row
            patternLineRowCounts[i] = 0;
            int pointsForRound = 0;


            // Calculate points for new tile placement and add to points
            // Count concurrent tiles in all directions of tile
            // Count horizontal (tiles to left and right)
            int horizontalTiles = tilesInDirection(row, column, DIRECTION_EAST) + tilesInDirection(row, column, DIRECTION_WEST);
            // Count vertical (tiles above and below)
            int verticalTiles = tilesInDirection(row, column, DIRECTION_NORTH) + tilesInDirection(row, column, DIRECTION_SOUTH);

            // If no adjacent tiles, add one point
            if (horizontalTiles == 0 && verticalTiles == 0){
                pointsForRound += 1;
            // If adjacent tiles found, then 
            } else {
                // If there are horizontal tiles, add amount of tiles plus the one that was just placed
                if (horizontalTiles != 0){

                    pointsForRound += horizontalTiles + 1;
                }
                
                // If there are vertical tiles, add amount of tiles plus the one that was just placed
                if (verticalTiles != 0){

                    pointsForRound += verticalTiles + 1;
                }
            }
            points += pointsForRound;
            rowsMoved.push_back(i);
            pointsEarned.push_back(pointsForRound);
        }
    } // end of for loop

    // Subtracts floor line values and empties tiles into lid
    // Also clears floor line
    pointSubtracted = 0;
    for (int r = 0; r < floorLineCount; r++){

        pointSubtracted += FLOOR_LINE_PENALTIES[r];
        // starting player tile doesn't go back into lid, gets deleted and re-created
        if (floorLine[r]->getType() != starter_player){

            game->addToBoxLid(floorLine[r]);
        } else {

            isFirstPlayer = true;
            delete floorLine[r];
        }
        floorLine[r] = nullptr;
    }
    points += pointSubtracted;
    if (points < 0){
        points = 0;
    }
    floorLineCount = 0;

    // Returns output value
    return isFirstPlayer;
}

int Player::tilesInDirection(int row, int column, int direction){
    // Tiles found in specified direction, will be returned
    int tileCount = 0;
    // Checks to see if direction is valid
    if (direction >= DIRECTION_NORTH && direction <= DIRECTION_WEST){
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
        if (direction == DIRECTION_NORTH){
            xIncrement = 0;
            yIncrement = -1;
            xEndPoint = -2;
            yEndPoint = -1;
        } else if (direction == DIRECTION_EAST){
            xIncrement = 1;
            yIncrement = 0;
            xEndPoint = WALL_DIMENSION;
            yEndPoint = -2;
        } else if (direction == DIRECTION_SOUTH){
            xIncrement = 0;
            yIncrement = 1;
            xEndPoint = -2;
            yEndPoint = WALL_DIMENSION;
        } else if (direction == DIRECTION_WEST){
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
            // Resets columns to leftmost one
            columnCount = 0;
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

void Player::updateEndGamePoints(){

    // Check for completed rows and columns
    for (int i = 0; i < WALL_DIMENSION; i++){
        // Check for completed rows
        if (tilesInDirection(i, -1, DIRECTION_EAST) == WALL_DIMENSION){
            points += 2;
        }
        // Check for completed columns
        if (tilesInDirection(-1, i, DIRECTION_SOUTH) == WALL_DIMENSION){
            points += 7;
        }
    }

    // Get counts for every colour (assumes same amount of colours as dimension of wall)
    int maxCount = WALL_DIMENSION;
    int counts[COLOUR_COUNT] = {0};
    Types colours[WALL_DIMENSION] = {Dark_Blue, Yellow, Red, Black, Light_Blue};

    // Go through every row and column of wall
    for (int i = 0; i < WALL_DIMENSION; i++){

        for (int r = 0; r < WALL_DIMENSION; r++){
            // If there is a tile then add to the count of that tiles colour
            if (wall[i][r] != nullptr){

                //Loop through all colours to check what colour it is, and add it to the totals
                for (int w = 0; w < COLOUR_COUNT; w++){

                    if (wall[i][r]->getType() == colours[w]){
                        counts[w]++;
                    }
                }
            }
        }
    }

    // Go through every colour count and if it is max, add points
    for (int i = 0; i < COLOUR_COUNT; i++){

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

            if (wall[i][j] != nullptr){
                data += wall[i][j]->getType();
            } else {
                data += '.';
            }
        }
        data += "\n";
    }

    return data;
}

std::string Player::getPatternLine(){
    std::string data = "";

    for(int i = 0; i < PATTERN_LINE_ROWS ; i++){

        for(int j = 0 ; j < i+1 ; j++){

            if (patternLines[i][j] != nullptr){
                data += patternLines[i][j]->getType();
            } else {
                data += '.';
            }
        }
        data += "\n";
    }

    return data;
}

std::string Player::getFloorLine(){
    std::string data = "";

    for(int i = 0; i < FLOOR_LINE_LENGTH; i++){

        if (floorLine[i] != nullptr){
            data += floorLine[i]->getType();
        } else {
            data += '.';
        }
    }

    return data;
}

void Player::setGame(Game* game){
    this->game = game;
}

bool Player::tileInRowOfWall(Types colour, int row){
    bool found = false;
    //if color found in row, means it exist in this row
    for(int i=0; i < WALL_DIMENSION ; i++){

        if(wall[row][i] != nullptr && wall[row][i]->getType() == colour){
            found = true;
        }
    }

    return found;
}


std::string Player::displayMosaic(){
    std::string displayOutput = "";
    displayOutput += "Mosaic for " + playerName + ":\n";

    // For every for of wall (and pattern line)
    for (int i = 0; i < WALL_DIMENSION; i++){

        displayOutput += std::to_string(i + 1) + ": ";

        // align pattern lines to right
        // Adds empty spaces for columns that don't exist
        for (int r = 0; r < WALL_DIMENSION - (i + 1); r++){
            displayOutput += "  ";
        }

        // Adds empty tiles . to represent columns that are unfilled
        for (int r = 0; r < ((i + 1) - patternLineRowCounts[i]); r++){
            displayOutput += ". ";
        }

        // Adds filled in tiles, aligned to right of the display
        for (int r = 0; r < patternLineRowCounts[i]; r++){

            // Check isnt needed
            if (patternLines[i][r] != nullptr){
                displayOutput += patternLines[i][r]->getType();
            } else {
                displayOutput += '.';
            }
            displayOutput += ' ';
        }
        // Add divider between pattern lines and wall
        displayOutput += "|| ";
        // Add wall
        for (int r = 0; r < WALL_DIMENSION; r++){

            if (wall[i][r] != nullptr){
                displayOutput += wall[i][r]->getType();
            } else {
                displayOutput += '.';
            }
            displayOutput += ' ';
        }
        // Move to next line
        displayOutput += '\n';
     // End of row loop
    }
    return displayOutput;
}
std::string Player::displayPenalty(){
    // Display floor line
    std::string displayOutput = "";
    displayOutput += "broken: ";

    for (int i = 0; i < floorLineCount; i++){

        std::string tileString(1, std::toupper(floorLine[i]->getType()));
        displayOutput += tileString + " ";
    }
    displayOutput += '\n';
    return displayOutput;
}

bool Player::canPlaceInPatternRow(Types colour, int patternRowIndex){
    bool canPlace = false;
    if (patternRowIndex >= 0 && patternRowIndex < PATTERN_LINE_ROWS){

        //if there is still space to put a tile
        if (patternLineRowCounts[patternRowIndex] < patternRowIndex + 1){

            //if the tile that's already in the row is of the same colour 
            if(patternLines[patternRowIndex][0] == nullptr || patternLines[patternRowIndex][0]->getType() == colour){
                
                //if tile of the colour not found in the wall 
                if(!tileInRowOfWall(colour, patternRowIndex)){
                    canPlace = true;
                }
            }
        }
        
    }
    return canPlace;
}