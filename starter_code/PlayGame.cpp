#include "PlayGame.h"
#include <iostream>

void startGame(Game* game){
    startGame(game, 0);
}

void startGame(Game* game, int startPlayer){
    bool gameRunning = true;
    int currentPlayerIndex = startPlayer;
    while (gameRunning){
        //Factory offer phase
        game->populateFactories();
        while (true){
            Player* player = game->getPlayer(currentPlayerIndex);
            std::cout << "TURN FOR PLAYER: " << player->getPlayerName() << std::endl;

            std::cout << "Factories:" << std::endl;
            std::cout << game->displayFactories() + "\n" << std::endl;

            std::cout << player->displayBoard();
            //Recieve input
            std::cout << ">";
            std::string commandInput = "";
            std::cin >> commandInput;
            if (std::cin.good() && commandInput == "turn"){

                // recieve factory, colour, storage row
                int factory = -1;
                char colourChar = '_'; // Underscore means invalid
                int patternRow = -1;
                bool validAction = true;
                
                std::cin >> factory >> colourChar >> patternRow;
                std::cin.clear();
                std::cout << "inputs" << factory << colourChar << patternRow << std::endl;
                Types colourType = readTypeFromChar(colourChar);
                // Initial checks, to make sure that input is within range to be checked
                // to prevent out of bounds error
                if (colourType != Invalid && factory >= 0 && factory < NUM_OF_FACTORIES + 1 &&
                  patternRow >= 0 && patternRow < PATTERN_LINE_ROWS + 1){
                    // check if tile can be placed in pattern row
                    // at least one 
                    if (player->canPlaceInPatternRow(colourType, patternRow - 1)){
                        // check to see if factory has a tile of desired colour, and
                        // if pattern row is for colour or if its empty
                        int tileAmount = -1;
                        Tile** tiles = nullptr;
                        // if factory chosen (not centre tiles)
                        if (factory != 0){
                            game->getTilesFromFactory(factory - 1, colourType, tileAmount, tiles);
                            // If any tiles were taken, then add tiles to player
                            if(tileAmount > 0){
                                // add tiles to pattern line of player
                                player->addTilesToPatternLine(tiles, tileAmount, patternRow - 1);
                            } else {
                                validAction = false;
                            }
                        } else if (factory == 0){
                            //center of table
                            bool isStartPlayer = game->getTilesFromCentre(colourType, tileAmount, tiles);
                            if(tileAmount > 0){
                                if (isStartPlayer){
                                    player->addToFloorLine(new Tile(starter_player));
                                }
                                player->addTilesToPatternLine(tiles, tileAmount, patternRow - 1);
                            } else {
                                validAction = false;
                            }
                        }
                    
                    } else {
                        
                    }
                }
            } else if (commandInput == "save"){
                std::string filename = "";
                bool saved;
                
                //get file name from player
                std::cin >> filename;

                //check if filename was entered
                if(filename != ""){
                    saved = saveGame(game, filename);

                    if(saved == false){
                        std::cout << "\nError: Saving failed..." << std::endl;
                    }
                }else{
                    std::cout << "\nPlease input a proper file name" << std::endl;
                }
                
            } else if(commandInput == "exit" || std::cin.eof()){
                //close the game
            } else{
                std::cout << "\nInvalid Input!" << std::endl;
            }
        }
    }
}

void nextPlayer(Game* game, int& currentPlayerIndex){
    if (currentPlayerIndex != game->getPlayerCount() - 1){
        currentPlayerIndex++;
    } else {
        currentPlayerIndex = 0;
    }
}
