#include "Game.h"
#include <random>

Game::Game(Player** playersToAdd, int playerCount){
    //add players given into players vector
    for(int i = 0; i < playerCount; i++){
        players.insert(players.end(), playersToAdd[i]);
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

    //set playerCount
    this->playerCount = playerCount;

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
          bool firstPlayerMarker) : players{ playersToAdd }, playerCount{ playerCount }, bag{ bag },
          factoryCount{ factoryCount }, factories{ factories }, centreTable{ centreTable }, boxLid{ boxLid },
          firstPlayerMarker{ firstPlayerMarker } {}


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
    for(int row = 0; row < NUM_OF_FACTORIES; row++){

        for(int col = 0; col < FACTORY_SIZE; col++){
            // TODO make random
            factories[row][col] = bag.back();
            bag.pop_back();
        }
    }
    
    
}


int Game::getPlayerCount(){
    return this->playerCount;
}


Player* Game::getPlayer(int index){
    Player* foundPlayer = nullptr;

    //checks if index is within player bounds
    if (index >= 0 && index < playerCount){
        foundPlayer = players[index];
    }
    return foundPlayer;
}


bool Game::getTilesFromFactory(int factoryIndex, Types colour, int& tileAmount, Tile** tiles){
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
            // As factory tiles has been removed, set output to true
            successfulFactoryRemoval = true;
        }
    }
    
    // Returns true if factory emptied, else false
    return successfulFactoryRemoval;
}


bool Game::getTilesFromCentre(Types colour, int& tileAmount, Tile** tiles){
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
    boxLid.insert(boxLid.end(), tile);
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
            data += factories[i][j]->getType();
        }
        data += "$\n";
    }
    data += '$';

    return data;
}


std::string Game::getCentreTable(){
    std::string data = "";

    if(centreTable->getSize() != 0){
        data += centreTable->getCenterTableDetails();
    }

    return data;
}
