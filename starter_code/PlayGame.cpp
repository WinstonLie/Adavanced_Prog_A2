#include "PlayGame.h"
#include <iostream>

void startGame(Game* game){
    startGame(game, 0);
}

void startGame(Game* game, int startPlayerIndex, bool fromLoadedGame){
    std::vector<std::string> commands;
    bool gameRunning = true;
    int currentPlayerIndex = startPlayerIndex;
    while (gameRunning){
        if (fromLoadedGame == false){
            //Factory offer phase
            game->populateFactories();
        } else {
            // Skips the factory population for first round of loaded games
            fromLoadedGame = false;
        }
        while (gameRunning && game->checkIfFactoriesPopulated()){
            Player* player = game->getPlayer(currentPlayerIndex);
            std::cout << "TURN FOR PLAYER: " << player->getPlayerName() << std::endl;

            std::cout << "Factories:" << std::endl;
            std::cout << game->displayFactories() + "\n" << std::endl;

            std::cout << player->displayMosaic();
            std::cout << player->displayPenalty();
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
                    patternRow > 0 && patternRow < PATTERN_LINE_ROWS + 2){

                    //Move tiles
                    validTurn = moveTiles(game, player, factory, colourType, patternRow);
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
                    saved = saveGame(game, currentPlayerIndex + 1, filename);

                    if(saved == false){
                        std::cout << "Error: Saving failed...\n" << std::endl;
                    }else{

                        std::cout << "Saved successfully to " << filename << std::endl;
                    }
                }else{
                    std::cout << "Please input a proper file name\n" << std::endl;
                }
                
            } else if(commandInput == "EXIT"){
                
                std::cout << "Game will exit without saving. Enter 'y' to quit game.)" << std::endl;
                
                char input = ' ';
                std::cin >> input;
                input = toupper(input);
                
                if(input == 'Y'){
                    
                    gameRunning = false;
                    
                }else {
                    
                    std::cout << "Continuing game..." << std::endl;
                    
                }
                
            }else if (std::cin.eof()){
                
                gameRunning = false; 
        
            } else{
                
                std::cout << "Invalid Input!\n" << std::endl;
            }
        } // end of factory offer phase while loop
    
        // Add tiles to wall, calculate points
        bool hasEndedGame = false;
        if (gameRunning){
            std::cout << "Round ended" << std::endl;

            //print all commands issued that round
            std::cout << "\n Commands Issued" << std::endl;
        
            for(int i = 0; i < commands.size(); i++){
                
                std::cout << commands[i] << std::endl;
            }
            //Add tiles into the wall
            //get round points for each player and details
            hasEndedGame = updateEndRoundDetails(game, currentPlayerIndex);
        }
        
        if (hasEndedGame){
            //get number of players
            int playerCount = game->getPlayerCount();
            std::vector<Player*> players;
            //add player to the vector after updating end game points
            for (int i = 0; i < playerCount; i++){

                Player* player = game->getPlayer(i);
                player->updateEndGamePoints();
                players.push_back(player);
            }
            //initialization of values for determining highest points of a player
            int highestPoints = -1;
            int highestPlayerIndex = 0;
            int currentRanking = 1;

            while (players.size() > 0){

                for (int i = 0; i < players.size(); i++){

                    if (players[i]->getPoints() > highestPoints){
                        //update highest ranking player and points
                        highestPlayerIndex = i;
                        highestPoints = players[i]->getPoints();
                    }
                }
                //printing out details
                std::cout << "Player rank " << currentRanking << ": "
                  << players[highestPlayerIndex]->getPlayerName() << " - "
                  << players[highestPlayerIndex]->getPoints() << " points" << std::endl; 
                
                //update players container
                players.erase(players.begin() + highestPlayerIndex);
                currentRanking++;
                highestPoints = -1;
                highestPlayerIndex = 0;
            }
            gameRunning = false;

            // calculate final points, decide winner and print results
        } else {
            //to next round
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

bool moveTiles(Game* game,Player* player, int factory, Types colourType, int patternRow){
    bool moved = false;
    // check to see if factory has a tile of desired colour, and
    // if pattern row is for colour or if its empty
    int tileAmount = -1;
    Tile** tiles = nullptr;
    // check if tile can be placed in pattern row
    // at least one 
    //or if patternRow is 6 -> place in broken
    if ((patternRow < 6 && player->canPlaceInPatternRow(colourType, patternRow - 1))
        || patternRow == 6){
        // if factory chosen (not centre tiles)
        if (factory > 0 && factory < NUM_OF_FACTORIES + 1){
            game->getTilesFromFactory(factory - 1, colourType, tileAmount, tiles);
            // If any tiles were taken, then add tiles to player
            if(tileAmount > 0){
                // Add to the board of player
                addToBoard(player,patternRow,tileAmount,tiles);
                moved = true;
            }
        // If wanting to take tiles from centre
        } else if (factory == 0){
            //center of table
            bool isStartPlayer = game->getTilesFromCentre(colourType, tileAmount, tiles);
            // If at least one tile is taken from the centre
            if(tileAmount > 0){
                // If they took the start player tile, then add it to the floor line
                if (isStartPlayer){
                    //Add starting player marker into the broken
                    player->addToFloorLine(new Tile(starter_player));
                }
                
                // Add to the board of player
                addToBoard(player, patternRow, tileAmount, tiles);
                moved = true;
            }
        }
    }
    return moved;   
}

void addToBoard(Player* player, int patternRow, int tileAmount, Tile** tiles){
    if (patternRow < 6){
        // add tiles to pattern line of player
        player->addTilesToPatternLine(tiles, tileAmount, patternRow - 1);
    // If patternRow is 6, then add to penalty
    } else {
        for(int i = 0; i < tileAmount; i++){
            player->addToFloorLine(tiles[i]);
        }
    } 
}

bool updateEndRoundDetails(Game* game,int currentPlayerIndex){
    bool hasEndedGame = false;
    for (int i = 0; i < game->getPlayerCount(); i++){
        Player* player = game->getPlayer(i);
        std::vector<int> rowsMoved;
        std::vector<int> pointsEarned;
        int pointsSubtracted = 0;
        bool hasTakenFirstPlayer = player->addTilesToWalls(rowsMoved, pointsEarned, pointsSubtracted);
        if (hasTakenFirstPlayer){
            currentPlayerIndex = i;
        }
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
        std::cout << "Overall points: " << player->getPoints() << std::endl;
        //Display all player mosaic at the end of a round
        std::cout << player->displayMosaic();
        std::cout << std::endl;

    }// end of for loop
    return hasEndedGame;
}