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
                char colour = '_'; // Underscore means invalid
                int storageRow = -1;
                
                std::cin >> factory  >> colour >> storageRow;
                std::cin.clear();
                std::cout << "inputs" << factory << colour << storageRow << std::endl;
                Types colour = readTypeFromChar(colour);
                // Initial checks, to make sure that input is within range to be checked
                // to prevent out of bounds error
                if (colour != Invalid && factory >= 0 && factory < NUM_OF_FACTORIES &&
                  storageRow >= 0 && storageRow < PATTERN_LINE_ROWS){
                    // check to see if factory has a tile of desired colour, and
                    // if pattern row is for colour or if its empty
                }
            } else if (commandInput == "save"){
                // recieve file path then save
            } else{
                std::cout << "Invalid Input!" << std::endl;
            }
        }
    }
}
