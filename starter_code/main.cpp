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

    std::cout << "Welcome to Azul" << std::endl;
    std::cout << "------------------" << std::endl;
    
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
    std::cout << "----"<< std::endl;

    std::cout << "1. New Game"<< std::endl;
    std::cout << "2. Load Game"<< std::endl;
    std::cout << "3. Credits"<< std::endl;
    std::cout << "4. Replay Game" << std::endl;
    std::cout << "5. Quit"<< std::endl;

}
//Checks the input
bool manageInput(char input){
    bool checked = false;
    
    //New Game
    if(input == '1'){
    
        std::cout << "Starting a New Game" << std::endl;
        std::cout << "-------------------" << std::endl;
        //Prompt user for input of player number
        std::string playerCoun = "";
        std::cout << "Number of Players: ";
        std::getline(std::cin, playerCoun);
        int playerCount = -1;
        bool validPlayerNumber = true;

        try{
            playerCount = std::stoi(playerCoun);

        }catch(std::invalid_argument e){

            validPlayerNumber = false;
        }
        //Prompt for information to start a new game
        if(validPlayerNumber && playerCount >=2 && playerCount <= 4){
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

            std::string centreInput = "";
            std::cout << "Would you like to use 2 CentreTables? (y/n) : ";
            std::getline(std::cin,centreInput);
            bool centreBool = false;
            bool validInput = false;

            //validation checks
            if(centreInput == "y" || centreInput == "Y"){
                centreBool = true;
                validInput = true;

            }else if(centreInput == "n" || centreInput == "N"){

                validInput = true;
            }else{

                validInput = false;
            }

            if(successfulConversion && validInput){
                Game* game = nullptr;
            // If a random seed was inserted, then use it in the game
            if (randomSeed != -1){
                game =  new Game(players, randomSeed,centreBool);
            // If no seed was inserted, use the default value set in Game.h
            } else {
                game =  new Game(players,centreBool);
            }
            // Starts the game
            startGame(game,0,false,false,centreBool);
            
            delete game;
            
            if (std::cin.eof()){

                std::cout << "Game closing due to end of file input..." << std::endl;
                checked = false;
                
            } else {
                checked = true;
            }
            }else{
                std::cout << "Invalid seed or Invalid Number of Centre Tables. Please enter a number" << std::endl;
                checked = true;
            }  
        }else{
            std::cout << "Invalid Number Of Players" <<  std::endl;
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
        bool fromLoadedGame = false;
        bool twoCentreFactories = false;
        loadGame(game, fileName, currentPlayerIndex, fromLoadedGame , twoCentreFactories);

        //validation if it was successfully loaded
        if (*game != nullptr){
            
            startGame(*game, currentPlayerIndex, fromLoadedGame,false,twoCentreFactories);

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

    //replay game
    else if(input == '4'){

        //get the file name, game must be completed
        std::cout << "\nPlease input file name" << std::endl;
        std::cout << ">" ; 
        std::string fileName = "";
        std::getline(std::cin, fileName);
        Game* game = nullptr;
        bool twoCentreFactories = false;

        game = loadGameForReplay(fileName, twoCentreFactories);

        if(game != nullptr){
            
            startGame(game,0,false,true,twoCentreFactories);

            delete game;

            checked = true;
        }else{

            std::cout << "Invalid File Name input!" << std::endl;
            checked = true;
        }

    }
    //Quit game
    else if(input == '5'){
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

