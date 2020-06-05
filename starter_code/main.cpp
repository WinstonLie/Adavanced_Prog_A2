#include <iostream>
#include <string>
#include "Game.h"
#include "SaveLoad.h"
#include "PlayGame.h"
#include <stdexcept>

void menuDisplay();

bool manageInput(char input);

void printCredits();

int main(void){

    std::cout << "\033[1m\033[36m" << "\n\nWelcome to Azul!!" << std::endl;
    std::cout << "-----------------" << "\033[0m" << std::endl;
    
    // Variable that loops main menu,
    // goes false when quitting or invalid input occurs
    bool menu_loop = true;
    
    while (menu_loop){
        
        // Displays main menu options
        menuDisplay();
        
        std::cout << "\n> ";
        
        // Inputs character from user
        std::string input;
        char inputChar = '_';
        std::getline(std::cin, input);

        if (input.size() == 1){
        
            //gets the first character of string
            inputChar = input[0];
        }
        
        std::cout << std::endl;

        // If not eof then process input
        // If eof or quitting then end loop
        if (std::cin.good()){

            menu_loop = manageInput(inputChar);
        } else {

            menu_loop = false;
        }
    }

    return EXIT_SUCCESS;
}

void menuDisplay(){
    
    std::cout << "\nMenu"<< std::endl;
    std::cout << "----" << std::endl;

    std::cout << "1. New Game"<< std::endl;
    std::cout << "2. Load Game"<< std::endl;
    std::cout << "3. Credits"<< std::endl;
    std::cout << "\033[31m" << "4. Quit"<< "\033[0m" << std::endl;

}
//Checks the input
bool manageInput(char input){
    bool checked = false;
    
    //New Game
    if(input == '1'){
    
        std::cout << "Starting a New Game" << std::endl;

        std::cout << "Please choose your game mode:" << std::endl;
        std::cout << "1. Normal" << std::endl;
        std::cout << "2. Grey Board" << std::endl;
        std::cout << "3. 6 Tile Board" << std::endl;

        std::cout << "> ";

        // choosing game mode they want to play
        std::string gameModeChosen;
        std::string gameMode;
        std::getline(std::cin, gameModeChosen);
        bool chosen = false;
        while(!chosen){
            if(gameModeChosen == "1"){
                gameMode = "Normal";
                chosen = true;
            }else if (gameModeChosen == "2"){
                // gameMode = "Grey";
                // chosen = true;
                std::cout << "Not yet implemented" << std::endl;
                std::getline(std::cin, gameModeChosen);
            }else if (gameModeChosen == "3"){
                // gameMode = "Six";
                // chosen = true;
                std::cout << "Not yet implemented" << std::endl;
                std::getline(std::cin, gameModeChosen);
            }else{
                std::cout << "Please choose from the list provided" << std::endl;
                std::getline(std::cin, gameModeChosen);
            }
        }
        // Can add prompt for player count if needed to extend
        int playerCount = 2;
        std::vector<Player*> players;

        for (int i = 0; i < playerCount; i++){

            std::cout << "Player " << i+1 << " name:" << std::endl;
            std::string playerName;
            std::getline(std::cin, playerName);

            players.insert(players.end(),new Player(playerName));
        }

        std::cout << "Insert seed or -1 for default:" << std::endl;
        std::string seedInput = "";
        std::getline(std::cin, seedInput);
        int randomSeed = -1;
        bool successfulConversion = true;

        try {
            randomSeed = std::stoi(seedInput);
        } catch (std::invalid_argument e){
            successfulConversion = false;
        }
    
        if(successfulConversion){
            Game* game = nullptr;
        // If a random seed was inserted, then use it in the game
        if (randomSeed != -1){
            game =  new Game(players, randomSeed);
        // If no seed was inserted, use the default value set in Game.h
        } else {
            game =  new Game(players);
        }
        // Starts the game
        startGame(game);
        
        delete game;
        
        if (std::cin.eof()){

            std::cout << "Game closing due to end of file input..." << std::endl;
            checked = false;
            
        } else {
            checked = true;
        }
        }else{
            std::cout << "Invalid seed. Please enter a number" << std::endl;
            checked = true;
        }  
    }
    //Load saved game
    else if(input == '2'){
        std::cout << "\nPlease input file name" << std::endl;
        std::cout << ">" ; 
        std::string fileName = "";
        std::getline(std::cin, fileName);

        Game** game = new Game*;
        *game = nullptr;
        int currentPlayerIndex = 0;
        bool isInProgress = false;
        bool fromLoadedGame = true;
        loadGame(game, fileName, currentPlayerIndex, isInProgress);

        //validation if it was successfully loaded
        if (*game != nullptr){
            startGame(*game, currentPlayerIndex, fromLoadedGame, isInProgress);

            //Deallocating memory for the game and game 
            delete *game;
            
            //check for end of file
            if (std::cin.eof()){

                std::cout << "Game closing due to end of file input" << std::endl;
                checked = false;

            } else {

                checked = true;

            }

        }else{
            std::cout << "Invalid File Name input!" << std::endl;
            checked = true;
        }

        // Deletes pointer to pointer of game
        delete game;
        
    }
    //gets credit
    else if(input == '3'){
        printCredits();
        checked = true;
    }
    //Quit game
    else if(input == '4'){
        std::cout << "Quitting The Game" << std::endl;
        checked = false;

    }else{
        std::cout << "Error: Invalid Input";
        std::cout <<  std::endl;
        checked = true;
    }
    return checked;
}

void printCredits(){
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "<Student 1>" << std::endl;
    std::cout << "Name: Winston ." << std::endl;
    std::cout << "Student ID: s3777969" << std::endl;
    std::cout << "Email: s3777969@student.rmit.edu.au" << std::endl;

    std::cout << "\n<Student 2>" << std::endl;
    std::cout << "Name: Jordan Sorrenti" << std::endl;
    std::cout << "Student ID: s3782534" << std::endl;
    std::cout << "Email: s3782534@student.rmit.edu.au" << std::endl;

    std::cout << "\n<Student 3>" << std::endl;
    std::cout << "Name: Rodrigo Miguel Rojas" << std::endl;
    std::cout << "Student ID: s3784466" << std::endl;
    std::cout << "Email: s3784466@student.rmit.edu.au" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

