#include "PlayGame.h"
#include <iostream>

void startGame(Game* game, int startPlayerIndex, bool fromLoadedGame, bool isInProgress, bool replayMode){
    
    // Boolean that keeps track of if the game is running
    // If false, then game loop ends
    bool gameRunning = true;
    bool gameExited = false;
    int commandIndex = 0;

    std::string gameMode = game->getGameMode();

    // Keeps track of the index of the current player
    int currentPlayerIndex = startPlayerIndex;

    // While the game is running
    while (gameRunning){

        // If the game wasn't just loaded, then set factories
        if (fromLoadedGame == false){
            //Factory offer phase
            game->populateFactories();
        } else {
            // Skips the factory population for first round of loaded games
            fromLoadedGame = false;
        }

        // Factory offer phase, this is where user does all input
        // Loop ends when all factories are empty
        while (gameRunning && game->checkIfFactoriesPopulated() && isInProgress){

            // Current player
            Player* player = game->getPlayer(currentPlayerIndex);
            
            // Displays information for user
            std::cout << "\n\n\033[36m" << "For help type " << "\033[1m\033[36m"  << "'Help'." << "\033[0m" << std::endl;
            std::cout << "TURN FOR PLAYER: " << "\033[1m\033[37m" << player->getPlayerName() << "\033[0m" << std::endl;

            std::cout << "Factories:" << std::endl;
            
            colorizeOutput(game->displayFactories());
            std::cout << std::endl;
            colorizeOutput(player->displayMosaic());
            colorizeOutput(player->displayPenalty());

            std::cout << "> ";

          
            //Recieve input from user
            // Gets whole line
            std::string commandLineInput = "";

            if(replayMode){
                bool ongoing = true;
                std::cout << "== REPLAY MODE ==" << std::endl;

                if(commandIndex < game->getCommands().size()){
                    std::cout << "For next turn type 'Next', to exit type 'Exit'" << std::endl;

                    std::string choice;

                    std::getline(std::cin, choice);
                    transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

                    if(choice == "NEXT"){
                    
                        std::string commandFromVector = game->getCommands()[commandIndex];
                        int splitIndex;
                        for(int i = 0; i < commandFromVector.length(); i++){
                            if(commandFromVector[i] == ')'){
                                splitIndex = i;
                            }
                        }

                        std::string name = commandFromVector.substr(1, splitIndex-1);
                        std::string turnCommand = commandFromVector.substr(splitIndex+4, commandFromVector.length());

                        std::cout << "\033[1m\033[36m\n\n" << "Turn " << commandIndex+1 << ": Player " << name << " executed command -> " << turnCommand << "\033[0m\n\n" << std::endl;
                        commandLineInput = turnCommand;
                        commandIndex++;
                        
                    }else if(choice == "EXIT"){

                        std::cout << "Quitting game..." << std::endl;
                        gameRunning = false;
                        gameExited = true;

                    }       
                }else{
                    std::cout << "latest command has been inputted. Would you like to resume game? (Yes/No)" << std::endl;

                    std::string resume;
                    std::getline(std::cin, resume);
                    transform(resume.begin(), resume.end(), resume.begin(), ::toupper);

                    if(resume == "YES"){

                        replayMode = false;
                        std::cout << "Resuming game..." << std::endl;
                        std::getline(std::cin, commandLineInput);

                    }else if(resume == "NO"){

                        std::cout << "Quitting game..." << std::endl;
                        gameRunning = false;
                        gameExited = true;

                    }else{

                        std::cout << "Invalid input" << std::endl;

                    }
                }
            }else{
                std::getline(std::cin, commandLineInput);
            }
            

            // Gets the first word of the line
            std::string commandInput = "";
            std::size_t currentLineIndex = 0;
            commandInput = getNextWord(commandLineInput, currentLineIndex);

            // If the user input "turn" as their first word
            if (std::cin.good() && commandInput == "TURN"){

                // recieve factory, colour, storage row
                int factory = -1;
                Types colourType = Invalid;
                int patternRow = -1;

                // Is set to true if turn is successful
                // Leads to current player being moved to next player
                bool validTurn = false;

                // Recieves factory, colour and patternRow from the input line
                processTurn(commandLineInput, currentLineIndex, factory,
                  colourType, patternRow);
 
                // Initial checks, to make sure that input is within range to be checked
                // to prevent out of bounds error
                if (colourType != Invalid && colourType != First_Player && factory >= 0 && factory < NUM_OF_FACTORIES + 1 &&
                    patternRow > 0 && patternRow < NORMAL_PATTERN_LINE_ROWS + 2){

                    //Move tiles
                    validTurn = moveTiles(game, player, factory, colourType, patternRow);
                }
                
                // If the turn was successful then move to next player
                if (validTurn){
                    std::cout << "\033[32m" << "Turn successful\n" << "\033[0m" << std::endl;

                    // Add command to vector of commands
                    std::string command = "(" +player->getPlayerName()
                      + ") > " + commandInput + " " + std::to_string(factory)
                      + " " + (char) colourType + " " + std::to_string(patternRow);

                    if(!replayMode){
                        game->addCommand(command);
                    }
                    
                    
                    //Switch to next player
                    nextPlayer(game, currentPlayerIndex);
                
                // If turn was unsuccessful then stay on same player
                } else {
                    std::cout << "\033[31m"  << "Turn unsuccessful\n" << "\033[0m" << std::endl;
                }
            
            // If the user insert "save" as their first word
            } else if (commandInput == "SAVE"){
                
                std::string filename = "";
                bool saved;
                
                //get file name from player
                filename = getNextWord(commandLineInput, currentLineIndex, false);

                //check if filename was entered
                if(filename != ""){
                    saved = saveGame(game, currentPlayerIndex + 1, filename, true);

                    if(saved == false){
                        std::cout << "Error: Saving failed...\n" << std::endl;
                    }else{

                        std::cout << "Saved successfully to " << filename << std::endl;
                    }
                }else{
                    std::cout << "Please input a proper file name\n" << std::endl;
                }
                
            // If the user inserted "exit" as their first word    
            } else if(commandInput == "EXIT"){
                
                std::cout << "\033[31m" << "Game will exit without saving. Enter 'y' to quit game.)" << "\033[0m" << std::endl;
                std::cout << "> ";

                std::string input = "";
                std::getline(std::cin, input);
                
                if(input.size() == 1 && toupper(input[0]) == 'Y'){
                    
                    gameRunning = false;
                    gameExited = true;
                    
                }else {
                    
                    std::cout << "Continuing game..." << std::endl;
    
                }
                
            // If eof has been found
            }else if (std::cin.eof()){
                
                gameRunning = false; 


            // User Interface Enhancement - HELP FUNCTION
            }else if (commandInput == "HELP") {

                bool exit = false;

                while(exit == false){
                    
                    std::cout << "\n \nAvailable Commands:" << std::endl;
                    std::cout << "'Turn <factory number> <color> <pattern row number>' to make a turn." << std::endl;
                    std::cout << "'Save <file name>' to save the game.'" << std::endl;
                    std::cout << "'Enemy' to see the board of your enemy." << std::endl;
                    std::cout << "'Replay' to watch a replay of the game until now." << std::endl;
                    std::cout << "'Exit' to leave the game.\n" << std::endl;
                    std::cout << "\033[32m" << "Type 'Return' to return to game\n \n" << "\033[0m" << std::endl;
                    std::cout << "\n> ";

                    std::string userInput;
                    std::getline(std::cin, userInput);
                    transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
                    if(userInput == "RETURN"){
                        exit = true;
                    }
                }
                
            //User Interface Enhancement - SEE ENEMY BOARD FUNCTION
            }else if (commandInput == "ENEMY"){
                
                bool exit = false;
                int playerNumber = currentPlayerIndex;

                if (playerNumber != game->getPlayerCount() - 1){
                    playerNumber++;
                } else {
                    playerNumber = 0;
                }

                Player* enemyPlayer = game->getPlayer(playerNumber);

                while(exit == false){
                    std::cout << "\n\n" << std::endl;
                    colorizeOutput(enemyPlayer->displayMosaic());
                    std::cout << "\n\n" << std::endl;

                    std::cout << "Type 'Return' to return to game\n \n" << std::endl;
                    std::cout << "\n> ";

                    std::string userInput;
                    std::getline(std::cin, userInput);
                    transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
                    if(userInput == "RETURN"){
                        exit = true;
                    }
                }
                 
            // Replay Enhancement 
            }else if (commandInput == "REPLAY"){
                
                gameRunning = false;
                gameExited = true;
                std::vector<Player*> players;

                for(int i = 0; i < game->getPlayerCount(); i++){
                    Player* player = game->getPlayer(i);
                    std::string playerName = player->getPlayerName();
                    players.push_back(new Player(playerName, game->getGameMode()));
                }

                int gameSeed = game->getRandomSeed();

                Game* replayGame = new Game(players, gameSeed);

                for(int i = 0; i < game->getCommands().size(); i++){
                    replayGame->addCommand(game->getCommands()[i]);
                }

                startGame(replayGame, 0, false, true, true);

            }else{
                
                std::cout << "Invalid Input!\n" << std::endl;
            }// end of command checking
            
        } // end of factory offer phase while loop
    
        // Add tiles to wall, calculate points

        bool hasEndedGame;
        if(isInProgress){
            hasEndedGame = false;
        }else{
            hasEndedGame = true;
        }
        

        if (gameRunning && !hasEndedGame){

            //print out commands of the round
            std::cout << "Round ended" << std::endl;
            std::vector<std::string> commands = game->getCommands();
            getCommands(commands);

            //Add tiles into the wall
            //get round points for each player and details
            hasEndedGame = updateEndRoundDetails(game, currentPlayerIndex);
        }
        
        if (hasEndedGame){
            
            //Print out end of game details including total points, winner and rankings
            updateEndGameDetails(game);

            gameRunning = false;

            // replay enhancement
            while(gameExited == false){
            std::cout << "\nGame Finished. Would you like to save, (type 'Save'), watch a replay (type 'Replay') or exit (type 'Exit')?\n" << std::endl;

            std::string response;

            std::getline(std::cin, response);

            transform(response.begin(), response.end(), response.begin(), ::toupper);

            if(response == "SAVE"){
                std::cout << "Please input a file name: ";
                std::string filename = "";
                std::getline(std::cin, filename);
                bool saved;

                //check if filename was entered
                if(filename != ""){
                    saved = saveGame(game, currentPlayerIndex + 1, filename, false);

                    if(saved == false){
                        std::cout << "Error: Saving failed...\n" << std::endl;
                    }else{

                        std::cout << "Saved successfully to " << filename << std::endl;
        
                    }
                }else{
                    std::cout << "Please input a proper file name\n" << std::endl;
                }
            }else if(response == "REPLAY"){

                gameRunning = false;
                gameExited = true;
                std::vector<Player*> players;

                for(int i = 0; i < game->getPlayerCount(); i++){
                    Player* player = game->getPlayer(i);
                    std::string playerName = player->getPlayerName();
                    players.push_back(new Player(playerName, game->getGameMode()));
                }

                int gameSeed = game->getRandomSeed();

                Game* replayGame = new Game(players, gameSeed);

                for(int i = 0; i < game->getCommands().size(); i++){
                    replayGame->addCommand(game->getCommands()[i]);
                }

                startGame(replayGame, 0, false, true, true);

            }else if(response == "EXIT"){
                std::cout << "\n\nThank you for playing Azul!!" << std::endl;
                gameRunning = false;
                gameExited = true;

            }else{
                
                std::cout << "Error: Invalid input..." << std::endl;

            }

            }
            
            // calculate final points, decide winner and print results
        } else {
            //to next round
        }

    }
}


void updateEndGameDetails(Game* game){
    
    std::cout << "=== GAME OVER ===\n " << std::endl;
    
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

}


void nextPlayer(Game* game, int& currentPlayerIndex){
    if (currentPlayerIndex != game->getPlayerCount() - 1){
        currentPlayerIndex++;
    } else {
        currentPlayerIndex = 0;
    }
}

bool moveTiles(Game* game,Player* player, int factory, Types colourType,
  int patternRow){
    
    // Represents if tiles were moved successfully
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
                    player->addToFloorLine(new Tile(First_Player));
                }
                
                // Add to the board of player
                addToBoard(player, patternRow, tileAmount, tiles);
                moved = true;
            }
        }
    }

    return moved;   
}

void addToBoard(Player* player, int patternRow, int tileAmount, Tile**& tiles){
    
    // If the pattern row inserted is actually a pattern row (and not the floor line)
    if (patternRow < 6){
        // add tiles to pattern line of player
        player->addTilesToPatternLine(tiles, tileAmount, patternRow - 1);

    // If patternRow is 6, then add to penalty
    } else {

        for(int i = 0; i < tileAmount; i++){
            player->addToFloorLine(tiles[i]);
        }
    }

    // Clean up tiles as it is no longer needed
    delete tiles;
    tiles = nullptr; 
}

bool updateEndRoundDetails(Game* game,int& currentPlayerIndex){
    bool hasEndedGame = false;

    // For every player in the game
    for (int i = 0; i < game->getPlayerCount(); i++){

        // Add the tiles from the pattern lines to the wall, if possible
        Player* player = game->getPlayer(i);
        std::vector<int> rowsMoved;
        std::vector<int> pointsEarned;
        int pointsSubtracted = 0;
        bool hasTakenFirstPlayer = player->addTilesToWalls(rowsMoved, pointsEarned, pointsSubtracted);

        // If the player had the first player index, then set them to be
        // the first player for next round
        if (hasTakenFirstPlayer){
            currentPlayerIndex = i;
        }

        // If at least one tile was moved to the wall
        if (rowsMoved.size() != 0){
            // Output the rows moved to the wall, and how many points each move earned
            std::cout << "Tiles moved to wall by " << player->getPlayerName() << ':' << std::endl;
            for (int r = 0; r < rowsMoved.size(); r++){

                std::cout << "Row " << rowsMoved[r] + 1 << " moved, gained "
                    << pointsEarned[r] << " points" << std::endl;
            }

            // If the player has a completed row, then set the game to end
            if (player->hasEndedGame()){
                hasEndedGame = true;
            }

        // If no tiles were moved to wall
        } else {
            std:: cout << "No tiles were moved to wall by " << player->getPlayerName() << std::endl;
        }

        // If any points were subtracted
        if (pointsSubtracted != 0){

            // Change points subtracted to a positive number
            pointsSubtracted *= -1;
            
            std::cout << pointsSubtracted << " points were subtracted due to the broken line" << std::endl;
        
        // If no points were subtracted
        } else {
            std::cout << "No penalty points were applied" << std::endl;   
        }

        // Displays the total points at the end of the round
        std::cout << "Overall points: " << player->getPoints() << std::endl;
        //Display all player mosaic at the end of a round
        std::cout << player->displayMosaic();
        std::cout << std::endl;

    }// end of for loop

    return hasEndedGame;
}

void getCommands(std::vector<std::string> commands){
    //print all commands issued that round
    std::cout << "\n Commands Issued" << std::endl;

    for(int i = 0; i < commands.size(); i++){
        
        std::cout << commands[i] << std::endl;
    }

}

bool processTurn(std::string line, std::size_t currentIndex, int& factory,
  Types& colourType, int& patternRow){
      // Expects three 'words' (inputs seperated by spaces) to be input
      int expectedInputs = 3;

      size_t currentPos = currentIndex;
      bool successfulInput = true;
      std::string words[expectedInputs];
      
      //loop through the input
      for (int i = 0; successfulInput && i < expectedInputs; i++){

          words[i] = getNextWord(line, currentPos,true);
          if (words[i] == ""){
              successfulInput = false;
          }
      }

      // If three words were detected
      if (successfulInput){

        if (words[1].size() == 1){

            // Reads the first chara
            colourType = readTypeFromChar(words[1][0]);

        } else {
            successfulInput = false;
        }

        try {

            factory = std::stoi(words[0]);
            patternRow = std::stoi(words[2]);
        } catch (std::invalid_argument e){
            successfulInput = false;
        }
      }

      return successfulInput;
}

std::string getNextWord(std::string line, std::size_t& currentIndex, bool toUpper){
    // Next word found in line, stays empty if not found
    std::string nextWord = "";

    std::size_t indexOfNextWord = -1;
    std::size_t indexOfLastChar = -1;

    try {
        //validate the input
        indexOfNextWord = line.find_first_not_of(' ', currentIndex);
        indexOfLastChar = line.find_first_of(' ', indexOfNextWord);
        
        // If there is no more spaces in line, then get last index
        if (indexOfLastChar == line.npos){
            indexOfLastChar = line.size();
        }

    } catch (std::exception e){
        // If exception was thrown, then set indexOfNextWord to fail next check
        indexOfNextWord = line.npos;
    }
    
    // If the start of the next word was found
    if (indexOfNextWord != line.npos){
        
        // Set the next word to be a substring of the word that was found
        nextWord = line.substr(indexOfNextWord, indexOfLastChar - indexOfNextWord);
        
        //make user input all uppercase, unless toUpper is false
        if (toUpper){
            
            // For each character in nextWord, make it capital
            for(int i = 0; i < nextWord.length(); i ++){
                nextWord[i] = toupper(nextWord[i]);
            }
        }

        // Set the current index to be the character after the last character
        // of word that was just read in
        currentIndex = indexOfLastChar + 1;
    }
    
    return nextWord;
}

// User Interface Enhancement - COLORIZATION OF OUTPUT
void colorizeOutput(std::string output){

    for(int i = 0; i < output.length(); i++){
        char toPrint = output[i];

        if(toPrint == '\n'){

            std::cout << "\n";

        }else{
            if(toPrint == 'R'){

                std::cout << "\033[1m\033[31m" << toPrint << "\033[0m";

            }else if(toPrint == 'Y'){

                std::cout << "\033[1m\033[33m" << toPrint << "\033[0m";

            }else if(toPrint == 'B'){

                std::cout << "\033[1m\033[34m" << toPrint << "\033[0m";

            }else if(toPrint == 'L'){

                std::cout << "\033[1m\033[36m" << toPrint << "\033[0m";

            }else if(toPrint == 'U'){

                std::cout << "\033[1m\033[30m" << toPrint << "\033[0m";

            }else if(toPrint == 'F'){

                std::cout << "\033[1m\033[32m" << toPrint << "\033[0m";

            }else{

                std::cout << toPrint;

            }
        }
        
    }
}