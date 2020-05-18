#include "PlayGame.h"
#include <iostream>

void startGame(Game* game){
    startGame(game, 0);
}

void startGame(Game* game, int startPlayerIndex){
    std::vector<std::string> commands;
    bool gameRunning = true;
    int currentPlayerIndex = startPlayerIndex;
    while (gameRunning){
        //Factory offer phase
        game->populateFactories();
        while (game->checkIfFactoriesPopulated()){
            Player* player = game->getPlayer(currentPlayerIndex);
            std::cout << "TURN FOR PLAYER: " << player->getPlayerName() << std::endl;

            std::cout << "Factories:" << std::endl;
            std::cout << game->displayFactories() + "\n" << std::endl;

            std::cout << player->displayBoard();
            //Recieve input
            std::cout << ">";
            std::string commandInput = "";
            std::cin >> commandInput;

            //make user input all uppercase
            for(int i = 0; i < commandInput.length(); i ++){
                commandInput[i] = toupper(commandInput[i]);
            }

            if (std::cin.good() && commandInput == "TURN"){

                // recieve factory, colour, storage row
                int factory = -1;
                char colourChar = '_'; // Underscore means invalid
                int patternRow = -1;
                bool validTurn = false;
                
                std::cin >> factory >> colourChar >> patternRow;
                
                //make user input uppercase
                colourChar = toupper(colourChar);
                std::string factoryString = std::to_string(factory);
                std::string patternRowString = std::to_string(patternRow);

                std::cin.clear();
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
                                validTurn = true;
                            }
                        // If wanting to take tiles from centre
                        } else if (factory == 0){
                            //center of table
                            bool isStartPlayer = game->getTilesFromCentre(colourType, tileAmount, tiles);
                            // If at least one tile is taken from the centre
                            if(tileAmount > 0){
                                // If they took the start player tile, then add it to the floor line
                                if (isStartPlayer){
                                    
                                    player->addToFloorLine(new Tile(starter_player));
                                }
                                // Add the tiles to the pattern line
                                player->addTilesToPatternLine(tiles, tileAmount, patternRow - 1);
                                validTurn = true;
                            }
                        }    
                    }
                }
                // If the turn was successful then move to next player
                if (validTurn){
                    std::cout << "Turn successful\n" << std::endl;
                    std::string command = "(" +player->getPlayerName() + ") > " + commandInput + " " + factoryString + " " + colourChar + " " + patternRowString;
                    commands.push_back(command);
                    
                    //Switch to next player
                    nextPlayer(game, currentPlayerIndex);
                // If turn was unsuccessful then stay on same player
                } else {
                    std::cout << "Turn unsuccessful\n" << std::endl;
                }
            } else if (commandInput == "SAVE"){
                std::string filename = "";
                bool saved;
                
                //get file name from player
                std::cin >> filename;

                //check if filename was entered
                if(filename != ""){
                    saved = saveGame(game, filename);

                    if(saved == false){
                        std::cout << "Error: Saving failed...\n" << std::endl;
                    }
                }else{
                    std::cout << "Please input a proper file name\n" << std::endl;
                }
                
            } else if(commandInput == "EXIT" || std::cin.eof()){
                //close the game or go to menu (ask Dale)
            } else{
                std::cout << "Invalid Input!\n" << std::endl;
            }
        } // end of factory offer phase while loop
        std::cout << "Round ended" << std::endl;

        //print all commands issued that round
        std::cout << "\n Commands Issued" << std::endl;
        for(int i = 0; i < commands.size(); i++){
            std::cout << commands[i] << std::endl;
        }

        // Add tiles to wall, calculate points
        bool hasEndedGame = false;
        for (int i = 0; i < game->getPlayerCount(); i++){
            Player* player = game->getPlayer(i);
            std::vector<int> rowsMoved;
            std::vector<int> pointsEarned;
            int pointsSubtracted = 0;
            player->addTilesToWalls(rowsMoved, pointsEarned, pointsSubtracted);
            if (rowsMoved.size() != 0){
                std::cout << "Tiles moved to wall by " << player->getPlayerName() << ':' << std::endl;
                for (int r = 0; r < rowsMoved.size(); r++){
                    std::cout << "Row " << rowsMoved[r] << " moved, gained "
                      << pointsEarned[r] << " points" << std::endl;
                }
                if (player->hasEndedGame()){
                    hasEndedGame = true;
                }
            } else {
                std:: cout << "No tiles were moved to wall by " << player->getPlayerName() << std::endl;
            }
            if (pointsSubtracted != 0){
                pointsSubtracted *= -1;
                std::cout << pointsSubtracted << " points were subtracted due to the broken line" << std::endl;
            } else {
                std::cout << "No penalty points were applied" << std::endl;   
            }
            std::cout << std::endl;
        }
        //Add tiles into the wall
        if (hasEndedGame){
            // calculate final points, decide winner and print results
        } else {
            //to next round
        }
        //Calculate scoring
    }
}

void nextPlayer(Game* game, int& currentPlayerIndex){
    if (currentPlayerIndex != game->getPlayerCount() - 1){
        currentPlayerIndex++;
    } else {
        currentPlayerIndex = 0;
    }
}
