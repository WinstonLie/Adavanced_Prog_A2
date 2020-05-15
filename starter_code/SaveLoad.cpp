#include "Game.h"
#include <ostream>
#include <istream>
#include <fstream>
#include <iostream>

Types readTypeFromChar(char input);

void readTiles(bool& validLoad, std::vector<std::string>& inputLines, 
  int& currentLineCounter, std::vector<Tile*>& tiles);

;bool checkLoad(bool& validLoad, std::vector<std::string>& inputLines, int currentLineCounter);

bool saveGame(Game* game, std::string filePath){
   bool successfullySaved = false;
   std::ofstream outputStream;
   outputStream.open(filePath);
   

   if(outputStream.good()){
       //save file tag
       outputStream << "#Saving File Tag" << std::endl;
       outputStream << "Fri 1630 - Dale" << std::endl;
       outputStream << std::endl;


       //date of saving
       outputStream << "#Save Date" << std::endl;
       outputStream << "GENERATE DATE HERE" << std::endl;
       outputStream << std::endl;


       //game status
       outputStream << "#Game Status" << std::endl;
       outputStream << "INSERT 1 IF ONGOING OR 0 IF FINISHED" << std::endl;
       outputStream << std::endl;


       //bag data
       outputStream << "#Bag" << std::endl;
       outputStream << game->getBag() << std::endl;
       outputStream << std::endl;


       //box lid data
       outputStream << "#Boxlid" << std::endl;
       outputStream << game->getBoxLid() << std::endl;
       outputStream << std::endl;


       //factory data
       outputStream << "#Factories" << std::endl;
       outputStream << game->getFactories() << std::endl;
       outputStream << std::endl;


       //centre table data
       outputStream << "#Centre Table" << std::endl;
       outputStream << game->getCentreTable() << std::endl;
       outputStream << std::endl;

       //player taking their turn
       outputStream << "#Current Player" << std::endl;
       outputStream << "INSERT Player Number??" << std::endl;
       outputStream << std::endl;


       //number of players
       outputStream << "#Number of Players" << std::endl;
       outputStream << game->getPlayerCount() << std::endl;
       outputStream << std::endl;
       
       
       //player 1 data
       outputStream << "#Player Status" << std::endl;
       outputStream << "#Player1" << std::endl;
       outputStream << game->getPlayer(0)->getPlayerName() << std::endl;
       outputStream << game->getPlayer(0)->getPoints() << std::endl;
       outputStream << std::endl;

       outputStream << "#Player1 Wall" << std::endl;
       outputStream << game->getPlayer(0)->getWall() << std::endl;
       outputStream << std::endl;

       outputStream << "#Player1 PatternLine" << std::endl;
       outputStream << game->getPlayer(0)->getPatternLine() << std::endl;
       outputStream << std::endl;

       outputStream << "#Player1 PenaltyPanel" << std::endl;
       outputStream << game->getPlayer(0)->getFloorLine() << std::endl;
       outputStream << std::endl;
       

       //player 2 data
       outputStream << "#Player2" << std::endl;
       outputStream << game->getPlayer(1)->getPlayerName() << std::endl;
       outputStream << "INSERT PLAYER SCORE" << std::endl;
       outputStream << std::endl;

       outputStream << "#Player2 Wall" << std::endl;
       outputStream << game->getPlayer(1)->getWall() << std::endl;
       outputStream << std::endl;

       outputStream << "#Player2 PatternLine" << std::endl;
       outputStream << game->getPlayer(1)->getPatternLine() << std::endl;
       outputStream << std::endl;

       outputStream << "#Player2 PenaltyPanel" << std::endl;
       outputStream << game->getPlayer(1)->getFloorLine() << std::endl;
       outputStream << std::endl;
       
       //successfully saved set to true
       successfullySaved = true;
   }
   
   outputStream.close();
   
   return successfullySaved;
}

bool loadGame(Game** game, std::string filePath){
    bool validLoad = true;
    // Read all valid lines from file into vector
    std::vector<std::string> inputLines;
    std::ifstream inputFileStream;
    inputFileStream.open(filePath);
    std::string currentLine;
    while (inputFileStream.good()){
        std::getline(inputFileStream, currentLine);
        if (!currentLine.empty() && currentLine[0] != '#' && currentLine[0] != '\r'){
            inputLines.push_back(currentLine);
        }
    }
    inputFileStream.close();
    for (int i = 0; i < inputLines.size(); i++){
        std::cout << inputLines[i] << std::endl;
    }
    
    // Create game from input
    // Create empty values for
    std::vector<Tile*> bag;
    std::vector<Tile*> boxLid;
    std::vector<Tile**> factories;
    int currentPlayerIndex;
    int numberOfPlayers;
    std::vector<Player*> players;
    bool firstPlayerMarker = true;

    // Counter for current line
    int currentLineCounter = 0;
    
    // Check save file tag
    if (checkLoad(validLoad, inputLines, currentLineCounter) &&
      inputLines[currentLineCounter].compare("Fri 1630 - Dale") == 0){
        currentLineCounter++;
    } else {
        std::cout << "invalid file line";
        validLoad = false;
    }

    // Check that no errors found so far and that there is a next line
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        // Check if the date is in the correct format
        // TODO
        currentLineCounter++;
    }

    // Get game status
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        // TODO
        currentLineCounter++;
    }

    // Read in bag
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        readTiles(validLoad, inputLines, currentLineCounter, bag);
    }

    // Read in box lid
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        readTiles(validLoad, inputLines, currentLineCounter, boxLid);
    }
    
    // Assumes 5 factories
    int factoryCount = 5;

    // Reads in factories
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        int factoryCounter = 0;
        while (validLoad && factoryCounter < factoryCount){
            std::vector<Tile*> input;
            readTiles(validLoad, inputLines, currentLineCounter, input);
            if (validLoad){
                factories.push_back(new Tile*[FACTORY_SIZE]);
                for (int i = 0; i < FACTORY_SIZE; i++){
                    if (i < input.size()){
                        factories[factoryCounter][i] = input[i];
                    } else {
                        factories[factoryCounter][i] = nullptr;
                    }
                }
                factoryCounter++;
            }
        }
    }

    // Read in seed
    // Not currently implemented

    // Current player
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        currentPlayerIndex = std::stoi(inputLines[currentLineCounter]);
        currentLineCounter++;
    }

    // Number of players
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        numberOfPlayers = std::stoi(inputLines[currentLineCounter]);
        currentLineCounter++;
        // Check to see that current player is within boundaries
        if (currentPlayerIndex < 0 || currentPlayerIndex >= numberOfPlayers){
            validLoad = false;
        }
    }

    // Read in players
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        // For every expected player, go through a loop
        int playerCounter = 0;
        while (validLoad && playerCounter < numberOfPlayers){
            // Initialise player variables
            std::string name = "";
            int points = -1;
            // Initialise empty wall
            Tile*** wall = new Tile**[WALL_DIMENSION];
            for (int i = 0; i < WALL_DIMENSION; i++){
                wall[i] = new Tile*[WALL_DIMENSION];
                for (int r = 0; r < WALL_DIMENSION; r++){
                    wall[i][r] = nullptr;
                }
            }
            // Initialise empty pattern lines
            Tile*** patternLines = new Tile**[PATTERN_LINE_ROWS];
            int* patternLineCounts = new int[PATTERN_LINE_ROWS];
            for (int i = 0; i < PATTERN_LINE_ROWS; i++){
                wall[i] = new Tile*[i + 1];
                patternLineCounts[i] = 0;
                for (int r = 0; r < i + 1; r++){
                    wall[i][r] = nullptr;
                }
            }

            Tile** floorLine = new Tile*[FLOOR_LINE_LENGTH];
            for (int i = 0; i < FLOOR_LINE_LENGTH; i++){
                floorLine[i] = nullptr;
            }
            int floorLineCount = 0;

            // Read in name
            if (checkLoad(validLoad, inputLines, currentLineCounter)){
                name = inputLines[currentLineCounter];
                currentLineCounter++;
            }

            // Read in points
            if (checkLoad(validLoad, inputLines, currentLineCounter)){
                std::cout << inputLines[currentLineCounter] << std::endl;
                points = std::stoi(inputLines[currentLineCounter]);
                currentLineCounter++;
            }

            // Read in wall
            

            int wallRowCounter = 0;
            while (checkLoad(validLoad, inputLines, currentLineCounter)
              && wallRowCounter < WALL_DIMENSION){
                // check that row has at least five characters
                if (inputLines[currentLineCounter].length() >= 5){
                    // Read in each character one by one
                    for (int i = 0; validLoad && i < WALL_DIMENSION; i++){
                        char input = inputLines[currentLineCounter][i];
                        Types type = readTypeFromChar(input);

                        if (type != Invalid && type != starter_player){
                            wall[wallRowCounter][i] = new Tile(type);
                        } else {
                            validLoad = false;
                        }
                    }
                    
                    wallRowCounter++;
                    currentLineCounter++;
                } else {
                    validLoad = false;
                }
            } // end of wall loading

            // Read in patternLines
            int patternRowCounter = 0;
            while (patternRowCounter < PATTERN_LINE_ROWS
              && checkLoad(validLoad, inputLines, currentLineCounter)){
                // check that row has at least five characters
                if (inputLines[currentLineCounter].length() >= patternRowCounter + 1){
                    // Boolean to check that all tiles are inserted at front
                    bool emptyTileFound = false;
                    // Read in each character one by one
                    for (int i = 0; validLoad && i < patternRowCounter + 1; i++){
                        char input = inputLines[currentLineCounter][i];
                        Types type = readTypeFromChar(input);

                        if (type != Invalid && type != starter_player){
                            if (type != Empty){
                                if (emptyTileFound){
                                    validLoad = false;
                                } else {
                                    patternLineCounts[patternRowCounter]++;
                                    patternLines[patternRowCounter][i] = new Tile(type);
                                }
                            }
                        } else {
                            validLoad = false;
                        }
                    }

                    
                    patternRowCounter++;
                    currentLineCounter++;
                } else {
                    validLoad = false;
                }
            } // end of pattern line loading

            // load in floor line
            if (checkLoad(validLoad, inputLines, currentLineCounter)){
                // Boolean to check that all tiles are inserted at front
                bool emptyTileFound = false;
                // check that floor line has enough characters
                if (inputLines[currentLineCounter].length() >= FLOOR_LINE_LENGTH){
                    // Read in floor line
                    for (int i = 0; validLoad && i < FLOOR_LINE_LENGTH; i++){
                        char input = inputLines[currentLineCounter][i];
                        Types type = readTypeFromChar(input);

                        if (type != Invalid){
                            if (type != Empty){
                                if (emptyTileFound || (type == starter_player && firstPlayerMarker == false)){
                                    validLoad = false;
                                } else {
                                    if (type == starter_player){
                                        firstPlayerMarker = false;
                                    }
                                    floorLineCount++;
                                    floorLine[i] = new Tile(type);
                                }
                            } else {
                                emptyTileFound = true;
                            }
                        } else {
                            validLoad = false;
                        }
                    }
                    currentLineCounter++;
                } else {
                    validLoad = false;
                }
            }

            // If load is valid so far, then create player with details
            if (validLoad){
                Player* player = new Player(name, points, patternLines,
                  patternLineCounts,  wall,  floorLine,  floorLineCount);
                players.push_back(player);
                playerCounter++;
            } else {
                // delete created objects for player
                // TODO
            }
        }

    }// end of reading in players

    // Creates game and adds in data if loaded successfully
    if (validLoad){
        LinkedList* centreTable = new LinkedList();// TODO add in values
        *game = new Game(players, numberOfPlayers, bag, factoryCount, 
          factories.data(), centreTable,  boxLid, firstPlayerMarker);
        std::cout << "valid load" << std::endl;
    } else {
        //delete created objects
        // TODO
        // std::cout << "invalid load" << std::endl;
    }

}
// checks that validLoad is true and that array counter is within range
bool checkLoad(bool& validLoad, std::vector<std::string>& inputLines, int currentLineCounter){
    bool checkedLoad;
    if (validLoad && inputLines.size() > currentLineCounter){
        checkedLoad = true;
    } else {
        std::cout << "invalid load" << std::endl;
        validLoad = false;
        checkedLoad = false;
    }
    return checkedLoad;
}

// Reads tiles until a $ character is reached
void readTiles(bool& validLoad, std::vector<std::string>& inputLines, 
  int& currentLineCounter, std::vector<Tile*>& tiles){
    int currentIndex = 0;
        char currentTile = inputLines[currentLineCounter][currentIndex];
        while (validLoad && currentTile != '$'){
            if (currentTile == '\n'){
                currentLineCounter++;
                currentIndex = 0;
            } else if (currentTile == ' ') {
                currentIndex++;
            } else {
                // starter_player is treated as unassigned
                Types colour = readTypeFromChar(currentTile);

                if (colour != Invalid && colour != starter_player){
                    tiles.push_back(new Tile(colour));
                    currentIndex++;
                } else {
                    validLoad = false;
                }
            }
            
            if (checkLoad(validLoad, inputLines, currentLineCounter)){
                currentTile = inputLines[currentLineCounter][currentIndex];
            } else {
                validLoad = false;
            }
        }// end of while
        currentLineCounter++;

}

// May potentially be moved to a util file for use in main program
Types readTypeFromChar(char input){
    Types colour = Invalid;
    if (input == 'R'){
        colour = Red;
    } else if (input == 'Y'){
        colour = Yellow;
    } else if (input == 'B'){
        colour = Dark_Blue;
    } else if (input == 'L'){
        colour = Light_Blue;
    } else if (input == 'U') {
        colour = Black;
    } else if (input == '.'){
        colour = Empty;  
    } else if (input == 'S'){
        colour = starter_player;
    }

    return colour;
}