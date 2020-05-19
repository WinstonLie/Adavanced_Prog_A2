#include "SaveLoad.h"
#include <ostream>
#include <istream>
#include <fstream>
#include <iostream>
#include <ctime>


bool saveGame(Game* game, int currentPlayer, std::string filePath){
   bool successfullySaved = false;
   std::ofstream outputStream;
   outputStream.open(filePath);
   

   if(outputStream.good()){
       //save file tag
       outputStream << "#Saving File Tag" << std::endl;
       outputStream << "Fri 1630 - Dale" << std::endl;
       outputStream << std::endl;


       time_t currentTime = time(0);
       char* saveTime = ctime(&currentTime);

       //date of saving
       outputStream << "#Save Date" << std::endl;
       outputStream << saveTime << std::endl;
       outputStream << std::endl;


       //game status
       outputStream << "#Game Status" << std::endl;
       outputStream << "GameInProgress: True" << std::endl;
       outputStream << std::endl;


       //bag data
       outputStream << "#Bag" << std::endl;
       outputStream << game->getBag() << std::endl;
       outputStream << std::endl;


       //box lid data
       outputStream << "#Boxlid" << std::endl;
       outputStream << game->getBoxLid() << std::endl;
       outputStream << std::endl;

       //centre table data
       outputStream << "#Centre Table" << std::endl;
       if (game->isFirstPlayerMarkerTaken() == false){
           outputStream << 'S';
       }
       outputStream << game->getCentreTable() << std::endl;
       outputStream << std::endl;

       //factory data
       outputStream << "#Factories" << std::endl;
       outputStream << game->getFactories() << std::endl;
       outputStream << std::endl;

       //player taking their turn
       outputStream << "#Current Player" << std::endl;
       outputStream << currentPlayer << std::endl;
       outputStream << std::endl;


       //number of players
       outputStream << "#Number of Players" << std::endl;
       outputStream << game->getPlayerCount() << std::endl;
       outputStream << std::endl;
       

       //player data
        for(int i = 0; i < game->getPlayerCount(); i++){
           Player* player = game->getPlayer(i);

            outputStream << "#Player Status" << std::endl;
            outputStream << "#Player" << i+1 << std::endl;
            outputStream << player->getPlayerName() << std::endl;
            outputStream << player->getPoints() << std::endl;
            outputStream << std::endl;

            outputStream << "#Player" << i+1 << " Wall" << std::endl;
            outputStream << player->getWall() << std::endl;
            outputStream << std::endl;

            outputStream << "#Player" << i+1 << " PatternLine" << std::endl;
            outputStream << player->getPatternLine() << std::endl;
            outputStream << std::endl;

            outputStream << "#Player" << i+1 << " PenaltyPanel" << std::endl;
            outputStream << player->getFloorLine() << std::endl;
            outputStream << std::endl;
        }
       
       //successfully saved set to true
       successfullySaved = true;
   }
   
   outputStream.close();
   
   return successfullySaved;
}

bool loadGame(Game** game, std::string filePath, int& currentPlayerIndex, bool& isInProgress){
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
    // // Code to print read in lines
    // for (int i = 0; i < inputLines.size(); i++){
    //     std::cout << inputLines[i] << std::endl;
    // }
    
    // Create game from input
    // Create empty values for game
    std::vector<Tile*> bag;
    std::vector<Tile*> boxLid;
    std::vector<Tile*> centreOfTable;
    Tile*** factories = nullptr;
    int numberOfPlayers;
    std::vector<Player*> players;

    // Is set to false if marker is found in a floor line
    bool firstPlayerMarker = true;
    isInProgress = false;

    // Counter for current line
    int currentLineCounter = 0;
    
    // Check save file tag
    if (checkLoad(validLoad, inputLines, currentLineCounter) &&
      inputLines[currentLineCounter].compare("Fri 1630 - Dale") == 0){
        currentLineCounter++;
    } else {
        validLoad = false;
    }

    // Check that no errors found so far and that there is a next line
    // Check date
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        // Nothing is to be done with the date, ignore this line
        currentLineCounter++;
    }

    // Get game status
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        std::size_t found = inputLines[currentLineCounter].find("True");
        isInProgress = (found != std::string::npos);
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
    
    // Read in the centre of table
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        readTiles(validLoad, inputLines, currentLineCounter, centreOfTable);
    }
    // TODO

    // Assumes 5 factories
    int factoryCount = 5;

    // Reads in factories
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        // Create array for factories
        factories = new Tile**[factoryCount];
        int factoryCounter = 0;
        // While loading is valid and there are still factories to load
        while (validLoad && factoryCounter < factoryCount){
            // Input the tiles for factory into the input vector
            std::vector<Tile*> input;
            readTiles(validLoad, inputLines, currentLineCounter, input);
            if (validLoad){
                // Create factory and input tiles into it
                Tile** factory = new Tile*[FACTORY_SIZE];
                for (int i = 0; i < FACTORY_SIZE; i++){
                    // If a tile is found, put it in else put in a nullptr
                    if (i < input.size()){
                        factory[i] = input[i];
                    } else {
                        factory[i] = nullptr;
                    }
                }
                // Add factory into factories array
                factories[factoryCounter] = factory;
                // Increment the factory counter, move on to next factory
                factoryCounter++;
            }
        }
    }

    // Read in seed
    // Not currently implemented

    // Current player
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        // Parse line into an integer for the current player
        currentPlayerIndex = std::stoi(inputLines[currentLineCounter]) - 1;
        currentLineCounter++;
    }

    // Number of players
    if (checkLoad(validLoad, inputLines, currentLineCounter)){
        // Parse line into an integer
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

                patternLines[i] = new Tile*[i + 1];
                patternLineCounts[i] = 0;
                for (int r = 0; r < i + 1; r++){

                    patternLines[i][r] = nullptr;

                }
            }

            // Initialise floor line
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
                // Parse points
                points = std::stoi(inputLines[currentLineCounter]);
                currentLineCounter++;
            }

            // Read in wall
            int wallRowCounter = 0;
            // While the loading is successful and still have rows left to load
            while (checkLoad(validLoad, inputLines, currentLineCounter)
              && wallRowCounter < WALL_DIMENSION){

                // check that row has at least five characters
                if (inputLines[currentLineCounter].length() >= WALL_DIMENSION){

                    // Read in each character one by one
                    for (int i = 0; validLoad && i < WALL_DIMENSION; i++){
                        char input = inputLines[currentLineCounter][i];
                        // Parse character into a type of tile
                        Types type = readTypeFromChar(input);

                        // If the type is valid for the wall, insert it into wall
                        if (type != Invalid && type != starter_player && type != Empty){

                            wall[wallRowCounter][i] = new Tile(type);

                        // If wall spot is empty, leave a nullptr
                        } else if (type == Empty) {

                            wall[wallRowCounter][i] = nullptr;
                        // If type is invalid or starter_player, then input is invalid
                        } else {

                            validLoad = false;
                        }
                    }
                    // Increment input line and counter for wall rows
                    wallRowCounter++;
                    currentLineCounter++;
                // If length of input is less than the expected columns, then loading is
                // incorrect
                } else {

                    validLoad = false;
                }
            } // end of wall loading

            // Read in patternLines
            int patternRowCounter = 0;
            while (patternRowCounter < PATTERN_LINE_ROWS
              && checkLoad(validLoad, inputLines, currentLineCounter)){

                // check that row has enough characters
                if (inputLines[currentLineCounter].length() >= patternRowCounter + 1){
                    // Boolean to check that all tiles are inserted at front
                    bool emptyTileFound = false;
                    
                    // Read in each character one by one
                    for (int i = 0; validLoad && i < patternRowCounter + 1; i++){
                        char input = inputLines[currentLineCounter][i];
                        // Parse character into a type of tile
                        Types type = readTypeFromChar(input);

                        // Checks that type is invalid
                        if (type != Invalid && type != starter_player){
                            // If type is empty then leave index as nullptr
                            if (type != Empty){
                                // If a tile has been found after an empty spot,
                                // then save file is incorrect 
                                if (emptyTileFound){
                                    validLoad = false;
                                } else {
                                    // Increase counter for that row and insert tile into row
                                    patternLineCounts[patternRowCounter]++;
                                    patternLines[patternRowCounter][i] = new Tile(type);
                                }
                            }
                        // If type is invalid or starter player, loading is invalid
                        } else {
                            validLoad = false;
                        }
                    }

                    // Increment row counter and input line counter
                    patternRowCounter++;
                    currentLineCounter++;
                // If length of line is less than expected, loading is invalid
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
                // Call loading contructor for player
                Player* player = new Player(name, points, patternLines,
                  patternLineCounts,  wall,  floorLine,  floorLineCount);
                // Push player into vector for players
                players.push_back(player);
                // Increase counter for how many players have been loaded
                playerCounter++;
            } else {
                // delete created objects for player
                // TODO
                // Go through pattern lines, wall and floor line
                // and remove any tiles found
                
                // Delete pattern line
                if (patternLines != nullptr){
                    for (int i = 0; i < PATTERN_LINE_ROWS; i++){

                        if (patternLines[i] != nullptr){

                            for (int r = 0; r < patternLineCounts[i]; r++){

                                if (patternLines[i][r] != nullptr){
                                    delete patternLines[i][r];
                                }
                            }
                            delete patternLines[i];
                        }
                    }
                    delete patternLines;
                }

                // Delete wall
                if (wall != nullptr){
                    for (int i = 0; i < WALL_DIMENSION; i++){
                        if (wall[i] != nullptr){
                            for (int r = 0; r < WALL_DIMENSION; r++){
                                if (wall[i][r] != nullptr){
                                    delete wall[i][r];
                                }
                            }
                            delete wall[i];
                        }
                    }
                    delete wall;
                }
                
                // Delete floor line
                if (floorLine != nullptr){
                    for (int i = 0; i < floorLineCount; i++){
                        if (floorLine[i] != nullptr){
                            
                            delete floorLine[i];
                        }
                    }
                    delete floorLine;
                }
            }
        }

    }// end of reading in players

    // Creates game and adds in data if loaded successfully
    if (validLoad){
        LinkedList* centreTable = new LinkedList(centreOfTable);
        // Calls loading constructor for Game
        *game = new Game(players, numberOfPlayers, new Bag(bag), factoryCount, 
          factories, centreTable,  new BoxLid(boxLid), firstPlayerMarker);
        // Confirms load is valid in console
        std::cout << "valid load" << std::endl;
    } else {
        //delete created objects
        // TODO
        // Deletes all tiles from respective tile vectors, if added
        std::vector<Tile*>* tileVectors[3] = {&bag, &boxLid, &centreOfTable};
        for (int i = 0; i < 3; i++){
            while ((*tileVectors[i]).size() > 0){
                delete (*tileVectors[i]).back();
                (*tileVectors[i]).pop_back();
            }
        }

        // Deletes players if they were added
        while (players.size() > 0){
            delete players.back();
            players.pop_back();
        }
        // Delete all factories
        if (factories != nullptr){
            for (int i = 0; i < NUM_OF_FACTORIES; i++){
                if (factories[i] != nullptr){
                    for (int r = 0; r < FACTORY_SIZE; r++){
                        if (factories[i][r] != nullptr){
                            delete factories[i][r];
                        }
                    }
                    delete factories[i];
                }
            }
            delete factories;
        }
    }

}
// checks that validLoad is true and that array counter is within range
bool checkLoad(bool& validLoad, std::vector<std::string>& inputLines, int currentLineCounter){
    bool checkedLoad;
    if (validLoad && inputLines.size() > currentLineCounter){
        checkedLoad = true;
    } else {
        validLoad = false;
        checkedLoad = false;
    }
    return checkedLoad;
}

// Reads tiles until a $ character is reached
// Doesn't expect empty tiles (represented as .)
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

                if (colour != Invalid){
                    // starter player will be added after for centre table
                    if (colour != starter_player){
                        tiles.push_back(new Tile(colour));
                    }
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