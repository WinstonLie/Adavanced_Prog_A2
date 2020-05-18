#include "Game.h"
#include <random>
#include <iostream>

Game::Game(std::vector<Player*> playersToAdd, int randomSeed) : randomSeed{ randomSeed }{
    //add players given into players vector
    players = playersToAdd;

    for (int i = 0; i < players.size(); i++){
        players[i]->setGame(this);
    }

    //populate bag with 20 of each color
    for(int i = 0; i < 20; i++){
        Tile* redTile = new Tile(Red); 
        Tile* yellowTile = new Tile(Yellow);
        Tile* darkBlueTile = new Tile(Dark_Blue);
        Tile* lightBlueTile = new Tile(Light_Blue);
        Tile* blackTile = new Tile(Black);
        
        bag.insert(bag.end(), redTile);
        bag.insert(bag.end(), yellowTile);
        bag.insert(bag.end(), darkBlueTile);
        bag.insert(bag.end(), lightBlueTile);
        bag.insert(bag.end(), blackTile);
    }

    //set factoryCount
    this->factoryCount = NUM_OF_FACTORIES;
    
    //set factories
    this->factories = new Tile**[NUM_OF_FACTORIES];
    for (int i = 0; i < NUM_OF_FACTORIES; i++){
        factories[i] = new Tile*[FACTORY_SIZE];
        for (int r = 0; r < FACTORY_SIZE; r++){
            factories[i][r] = nullptr;
        }
    }
    
    //set centreTable
    this->centreTable = new LinkedList();

    //set firstPlayerMarker
    this->firstPlayerMarker = true;
}

Game::Game (std::vector<Player*> playersToAdd, int playerCount, std::vector<Tile*> bag,
          int factoryCount, Tile*** factories, LinkedList* centreTable, std::vector<Tile*> boxLid,
          bool firstPlayerMarker, int randomSeed) : players{ playersToAdd }, bag{ bag },
          factoryCount{ factoryCount }, factories{ factories }, centreTable{ centreTable }, boxLid{ boxLid },
          firstPlayerMarker{ firstPlayerMarker }, randomSeed{ randomSeed } {}


Game::~Game(){

    //delete all deletable variables
    players.clear();
    bag.clear();
    delete factories;
    delete centreTable;
    boxLid.clear();
}


void Game::populateBagFromLid(){
    //iterate through the whole box lid
    for(std::vector<Tile*>::iterator it = boxLid.begin(); it < boxLid.end(); it++){
        //add tiles from box lid into bag
        bag.insert(bag.end(), *it);
        //remove tile from box lid without deleting the tile
        boxLid.erase(it);
    }
}


void Game::populateFactories(){
    //check for number of tiles in bag
    if (bag.size() < FACTORY_SIZE * factoryCount){
        //put everything in to bag if less
        populateBagFromLid();
    }
    //random engine initialisation with seed
    std::default_random_engine engine(randomSeed);
    
    for(int row = 0; row < NUM_OF_FACTORIES; row++){

        for(int col = 0; col < FACTORY_SIZE; col++){
            int min = 0;
            int max = bag.size() - 1;
            
            std::uniform_int_distribution<int> uniform_dist(min,max);
            // make random
            //initializing random values to populate factrories
            int value = uniform_dist(engine);
            factories[row][col] = bag[value];
            bag.erase(bag.begin() + value);
        }
    }
    
    
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
    // TODO change code so nothing is taken if no tiles match colour
    
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
        if (factories[factoryIndex][0] != nullptr){
            //check if there exists a tile of the specific colour in the specific row
            if(checkColourExistence(factoryIndex, colour)){
                 // Loops through every spot in factory
                for (int i = 0; i < FACTORY_SIZE; i++){
                    // If the spot in the factory matches colour, then put it into output array
                    if (factories[factoryIndex][i]->getType() == colour){
                        tiles[tileAmount] = factories[factoryIndex][i];
                        tileAmount++;
                    // If not matching colour, then put it into the centre
                    } else {
                        centreTable->insert(factories[factoryIndex][i]);
                    }
                    // Remove the tile pointer from the factory
                    factories[factoryIndex][i] = nullptr;
                }
            }
            // As factory tiles has been removed, set output to true
            successfulFactoryRemoval = true;
        }
    }
    
    // Returns true if factory emptied, else false
    return successfulFactoryRemoval;
}


bool Game::getTilesFromCentre(Types colour, int& tileAmount, Tile**& tiles){
    //Amount of tiles that are in tiles
    tileAmount = 0;

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
            hasTakenFirstPlayer = true;
            firstPlayerMarker = false;
        }

    }

    return hasTakenFirstPlayer;
}


bool Game::isFirstPlayerMarkerTaken(){
    return firstPlayerMarker;
}


void Game::addToBoxLid(Tile* tile){
    //insert into boxLid vector
    boxLid.push_back(tile);
}


std::string Game::getBag(){
    std::string data = "";

    for(int i = 0; i < bag.size(); i++){
        data += bag[i]->getType();
    }
    data += '$';

    return data;
}


std::string Game::getBoxLid(){
    std::string data = "";

    for(int i = 0; i < boxLid.size(); i++){
        data += boxLid[i]->getType();
    }
    data += '$';

    return data;
}


std::string Game::getFactories(){
    std::string data = "";

    for(int i = 0; i < NUM_OF_FACTORIES; i++){
        for(int j = 0; j < FACTORY_SIZE ; j++){
            if (factories[i][j] != nullptr){
                data += factories[i][j]->getType();
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
        tilesInFactories += "S ";
    }
    if(centreTable->getSize() > 0){
        tilesInFactories += centreTable->getTilesFromCenterTable() + "\n";
    } else {
        tilesInFactories += "\n";
    }
    for(int i=0;i< NUM_OF_FACTORIES;i++){
        tilesInFactories += std::to_string(i+1) + ": ";
        for(int j=0;j < FACTORY_SIZE ; j++){

            if (factories[i][j] == nullptr){
                //Display nothing if no tile
                tilesInFactories += "  ";

            }else{
                tilesInFactories += std::toupper(factories[i][j]->getType()) + ' ';
            }
        }
        tilesInFactories += "\n";
    }

    return tilesInFactories;
}

bool Game::checkIfFactoriesPopulated(){
    bool populated = false;
    //Check for centreTable to see if there is any tiles
    if(centreTable->getSize() > 0){
        populated = true;
    }
    //Check for factories 1 to 5
    for(int row = 0; row < NUM_OF_FACTORIES ; row++){
        for(int col = 0; col < FACTORY_SIZE ; col++){
            if(factories[row][col] != nullptr){
                populated = true;
            }
        }
    }
    return populated;
}

int Game::getRandomSeed(){
    return randomSeed;
}

bool Game::checkColourExistence(int row, Types colour){
    bool exists = false;
    for (int i = 0; i < FACTORY_SIZE; i++){
        if (factories[row][i]->getType() == colour){
            exists = true;
        }
    }
    return exists;
}
