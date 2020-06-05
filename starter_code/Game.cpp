#include "Game.h"
#include <random>
#include <iostream>

Game::Game(std::vector<Player*> playersToAdd, std::string gameMode, int randomSeed) : gameMode { gameMode }, randomSeed{ randomSeed }{
    bag = new Bag();
    boxLid = new BoxLid();

    //add players given into players vector
    players = playersToAdd;

    for (int i = 0; i < players.size(); i++){

        players[i]->setGame(this);
    }

    //populate bag with 20 of each color
    for(int i = 0; i < TILES_PER_COLOUR; i++){

        Tile* redTile = new Tile(Red); 
        Tile* yellowTile = new Tile(Yellow);
        Tile* darkBlueTile = new Tile(Dark_Blue);
        Tile* lightBlueTile = new Tile(Light_Blue);
        Tile* blackTile = new Tile(Black);

        bag->insertIntoBag(redTile);
        bag->insertIntoBag(yellowTile);
        bag->insertIntoBag(darkBlueTile);
        bag->insertIntoBag(lightBlueTile);
        bag->insertIntoBag(blackTile);

        if(this->gameMode == "Six"){
            Tile* orangeTile = new Tile(Orange);
            bag->insertIntoBag(orangeTile);
        }
    }

    //set factoryCount
    this->factoryCount = NUM_OF_FACTORIES;
    
    factories = new Factory*[NUM_OF_FACTORIES];
    for (int i = 0; i < NUM_OF_FACTORIES; i++){
        factories[i] = new Factory();
    }

    //set centreTable
    this->centreTable = new CentreTable();

    //set firstPlayerMarker
    this->firstPlayerMarker = true;
}


Game::Game (std::vector<Player*> playersToAdd, std::string gameMode, int playerCount, Bag* bag,
          int factoryCount, Factory** factories, CentreTable* centreTable, BoxLid* boxLid,
          bool firstPlayerMarker, std::vector<std::string> commands, int randomSeed) : players{ playersToAdd }, gameMode { gameMode }, bag{ bag },
          factoryCount{ factoryCount }, factories{ factories }, centreTable{ centreTable }, boxLid{ boxLid },
          firstPlayerMarker{ firstPlayerMarker }, commands{ commands }, randomSeed{ randomSeed }{
            
            //initializing players to the game
            for (int i = 0; i < players.size(); i++){

                players[i]->setGame(this);
            }
          }


Game::~Game(){

    //delete all deletable variables
    for(int i =0 ; i < players.size(); i++){
        delete players[i];
    }
    
    //deleting factories
    for (int i = 0; i < NUM_OF_FACTORIES; i++){
        delete factories[i];
    }

    //deleting game components
    delete bag;
    delete factories;
    delete centreTable;
    delete boxLid;
}


void Game::populateBagFromLid(){

    int lidSize = boxLid->getSize();
    while (lidSize > 0){

        //insertion into bag and remove from lid
        int lastLidIndex = lidSize - 1;
        bag->insertIntoBag(boxLid->get(lastLidIndex));
        boxLid->removeFromBoxLid(lastLidIndex);
        lidSize--;
    }
}


void Game::populateFactories(){

    //check for number of tiles in bag
    if (bag->getSize() < FACTORY_SIZE * factoryCount){
        //put everything in to bag if less
        populateBagFromLid();
    }

    //random engine initialisation with seed
    std::default_random_engine engine(randomSeed);

    
    for(int row = 0; row < NUM_OF_FACTORIES; row++){

        Tile** tiles = new Tile*[FACTORY_SIZE];

        for(int col = 0; col < FACTORY_SIZE; col++){
            // Set min and max values to randomize between
            int min = 0;
            int max = bag->getSize() - 1;
            
            std::uniform_int_distribution<int> uniform_dist(min,max);

            //Get random value
            int value = uniform_dist(engine);

            // Get a tile from the randomised index of the bag
            tiles[col] = bag->get(value);

            // Remove that tile from the bag
            bag->removeFromBag(value);
        }

        // Set the tiles recieved from the bag into a factory
        factories[row]->setTiles(tiles, FACTORY_SIZE);
    }

    // Reset the first player marker
    firstPlayerMarker = true;
}


int Game::getPlayerCount(){
    return players.size();
}


Player* Game::getPlayer(int index){
    Player* foundPlayer = nullptr;

    //checks if index is within player bounds
    if (index >= 0 && index < players.size()){
        foundPlayer = players[index];
    }

    return foundPlayer;
}


bool Game::getTilesFromFactory(int factoryIndex, Types colour, int& tileAmount, Tile**& tiles){
    
    // Output boolean, changes to true if factory is emptied
    bool successfulFactoryRemoval = false;
    
    // Amount of tiles that are in tiles
    tileAmount = 0;

    // Deletes tiles if set, then creates new array of max amount of tiles
    delete tiles;
    tiles = new Tile*[FACTORY_SIZE];

    // Checks that index is within range
    if (factoryIndex >= 0 && factoryIndex < factoryCount){

        // Checks that factory is not empty
        if (factories[factoryIndex]->hasTiles()){
            
            // Creates new variables to house the values that go to the centre
            Tile** centreTiles = nullptr;
            int centreTilesCount = -1;

            // Get the values from the factory
            factories[factoryIndex]->getTiles(colour, tiles, tileAmount,
                centreTiles, centreTilesCount);

            // If tile amount is not zero, then method was successful in getting tiles
            if(tileAmount != 0){
               
                // Add all centre tiles into the centre
                for (int i = 0; i < centreTilesCount; i++){
                    centreTable->insert(centreTiles[i]);
                }
                   // As factory tiles has been removed, set output to true
                successfulFactoryRemoval = true;
            }
            // As centreTiles array is no longer needed, delete it
            delete centreTiles;

            
        }
    }
    
    // Returns true if factory emptied, else false
    return successfulFactoryRemoval;
}


bool Game::getTilesFromCentre(Types colour, int& tileAmount, Tile**& tiles){
    //Amount of tiles that are in tiles
    tileAmount = 0;

    // Boolean to return, is true if they are recieving the first player marker
    bool hasTakenFirstPlayer = false;
    
    //Deletes tiles if set, then creates new array of max amount of tiles
    delete tiles;
    int centreTableSize = centreTable->getSize();
    tiles = new Tile*[centreTableSize];

    //Checks if centreTable is empty
    if(centreTableSize != 0){
        
        //remove tiles from centreTable and add to tiles array
        centreTable->removeTiles(colour, tiles, tileAmount);

        //checks if it is first time taking from centreTable
        if (firstPlayerMarker){
            // If they are, then give player the tile by removing it from game
            // and adding it to return
            hasTakenFirstPlayer = true;
            firstPlayerMarker = false;
        }

    }

    return hasTakenFirstPlayer;
}


bool Game::isFirstPlayerMarkerTaken(){
    return !firstPlayerMarker;
}


void Game::addToBoxLid(Tile* tile){
    //insert into boxLid vector
    boxLid->insertIntoBoxLid(tile);
}


std::string Game::getBag(){
    std::string data = "";

    for(int i = 0; i < bag->getSize(); i++){
        data += bag->get(i)->getType();
    }
    data += '$';

    return data;
}


std::string Game::getBoxLid(){
    std::string data = "";

    for(int i = 0; i < boxLid->getSize(); i++){
        data += boxLid->get(i)->getType();
    }
    data += '$';

    return data;
}


std::string Game::getFactories(){
    std::string data = "";

    for(int i = 0; i < NUM_OF_FACTORIES; i++){

        std::string tileString = factories[i]->getTileString();

        if (tileString.size() != 0){

            for(int j = 0; j < FACTORY_SIZE ; j++){

                data += tileString[j];
            }

        }
        
        data += "$\n";
    }

    return data;
}


std::string Game::getCentreTable(){
    std::string data = "";
    if(centreTable->getSize() != 0){
        data += centreTable->getCenterTableDetails();
    } else {
        data += '$';
    }

    return data;
}

std::string Game::displayFactories(){
    std::string tilesInFactories = "";
    tilesInFactories += "0: ";

    if (firstPlayerMarker){

        tilesInFactories += "F ";
    }

    if(centreTable->getSize() > 0){

        tilesInFactories += centreTable->getTilesFromCenterTable() + "\n";
    } else {

        tilesInFactories += "\n";
    }
    for(int i=0 ;i < NUM_OF_FACTORIES ; i++){

        tilesInFactories += std::to_string(i+1) + ": ";
        std::string tileString = factories[i]->getTileString();
        for(int j=0;j < FACTORY_SIZE ; j++){

            if (tileString.size() == 0){
                //Display nothing if no tile
                tilesInFactories += "  ";

            }else{
                //accumulating tile types to display
                char tileType = tileString[j];
                tileType = toupper(tileType);
                std::string s(1, tileType);
                tilesInFactories += s + " ";
            }
        }
        tilesInFactories += "\n";
    }

    return tilesInFactories;
}

bool Game::checkIfFactoriesPopulated(){

    // Value to return, signifies if at least one factory has tiles in it
    bool populated = false;
    
    //Check for centreTable to see if there is any tiles
    if(centreTable->getSize() > 0){
        
        populated = true;
    }
    
    //Check for factories 1 to 5 until a tile has been found
    for(int row = 0; populated == false && row < NUM_OF_FACTORIES ; row++){
        
        // Checks if factory has any tiles
        if (factories[row]->hasTiles()){
            populated = true;
        }

    }
    
    return populated;
}

int Game::getRandomSeed(){
    return randomSeed;
}

std::vector<std::string> Game::getCommands(){
    return this->commands;
}

void Game::addCommand(std::string commandToAdd){
    commands.push_back(commandToAdd);
}

std::string Game::getGameMode(){
    return this->gameMode;
}
