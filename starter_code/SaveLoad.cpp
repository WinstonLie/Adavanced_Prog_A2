#include "Game.h"
#include <ostream>
#include <istream>
#include <fstream>
#include <iostream>


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

bool loadGame(Game* game, std::string filePath){
    bool validLoad = true;
    // Read all valid lines from file into vector
    std::vector<std::string> inputLines;
    std::ifstream inputFileStream;
    inputFileStream.open(filePath);
    std::string currentLine;
    inputFileStream >> currentLine;
    while (inputFileStream.good()){
        if (currentLine.length() != 0 && currentLine[0] != '#'){
            inputLines.push_back(currentLine);
        }
        inputFileStream >> currentLine;
    }
    inputFileStream.close();
    
    // Create game from input
    // Create empty values for
    std::vector<Tile*> bag;
    std::vector<Tile*> boxLid;
    std::vector<Tile**> factories;

    // Counter for current line
    int currentLineCounter = 0;
    
    // Check save file tag
    if (checkLoad(validLoad, inputLines, currentLineCounter) &&
      inputLines[currentLineCounter] == "Fri 1630 - Dale"){
        currentLineCounter++;
    } else {
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

}
//
bool checkLoad(bool validLoad, std::vector<std::string>& inputLines, int currentLineCounter){
    bool checkedLoad;
    if (validLoad && inputLines[currentLineCounter].length() > currentLineCounter){
        checkedLoad = true;
    } else {
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
                Types colour = starter_player;
                if (currentTile == 'R'){
                    colour = Red;
                } else if (currentTile == 'Y'){
                    colour = Yellow;
                } else if (currentTile == 'B'){
                    colour = Dark_Blue;
                } else if (currentTile == 'L'){
                    colour = Light_Blue;
                } else if (currentTile == 'U') {
                    colour = Black;
                }

                if (colour != starter_player){
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
        }

}