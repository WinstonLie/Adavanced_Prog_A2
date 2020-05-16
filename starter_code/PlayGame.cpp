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
                std::string factory = "-1";
                std::string colour = "-1";
                std::string storageRow = "-1";
                
                std::cin >> factory  >> colour >> storageRow;
                std::cin.clear();
                std::cout << "inputs" << factory << colour << storageRow << std::endl;
            } else if (commandInput == "save"){
                // recieve file path then save
            } else{
                std::cout << "Invalid Input!" << std::endl;
            }
        }
    }
}
