#include "Factory.h"

Factory::Factory(){

    // Initialise tile array and set elements to nullptr
    factory = new Tile*[FACTORY_SIZE];

    for (int i = 0; i < FACTORY_SIZE; i++){
        factory[i] = nullptr;
    }

}

Factory::~Factory(){
    //Deletes all tiles in array, then the array itself
    for (int i = 0; i < FACTORY_SIZE; i++){
        if (factory[i] != nullptr){
            delete factory[i];
        }
    }

    delete factory;
}


Factory::Factory(Tile** tiles) : factory{ tiles }{}


bool Factory::hasTiles(){
    // Checks to see if first element is set, if it is then it has tiles
    // Works as factory is only ever full or empty, never between
    bool hasTiles = false;

    if (factory[0] != nullptr){
        hasTiles = true;
    }

    return hasTiles;
}

bool Factory::hasColour(Types colour){
    bool hasColour = false;

    // Checks if the factory has tiles
    if (hasTiles()){
        // Goes through every element in factory to check if it has the colour
        for (int i = 0; hasColour == false && i < FACTORY_SIZE; i++){
            if (factory[i]->getType() == colour){
                hasColour = true;
            }
        }
    }

    return hasColour;
}

bool Factory::setTiles(Tile** tiles, int tileCount){

    bool successfullySet = false;
    
    // If the tiles input match the size of the factory, set their pointers
    // as the factory tiles
    if (tileCount == FACTORY_SIZE){
    
        for (int i = 0; i < FACTORY_SIZE; i++){

            factory[i] = tiles[i];
    
        }
        successfullySet = true;
    }

    return successfullySet;
}

void Factory::getTiles(Types colour, Tile**& tiles, int& tileCount, Tile**& centreTiles,
  int& centreTilesCount){

    // Initialise reference parameters
    tileCount = 0;
    centreTilesCount = 0;
    tiles = nullptr;
    centreTiles = nullptr;

    // Check to see if colour exists in factory
    if (hasColour(colour)){

        // Sets arrays to max amount of tiles that could be found
        // The inefficiency won't matter too much, these arrays
        //   will be deleted very soon
        tiles = new Tile*[FACTORY_SIZE];
        // Since at least one tile must be of the colour, max size is -1
        centreTiles = new Tile*[FACTORY_SIZE];

        // Go through every element in the factory, moving each tile into
        //  the appropriate array
        for (int i = 0; i < FACTORY_SIZE; i++){

            // If tile matches colour, then add it to output
            if (factory[i]->getType() == colour){
                tiles[tileCount] = factory[i];
                tileCount++;
            // If it doesn't match, add it to the centre array
            } else {
                centreTiles[centreTilesCount] = factory[i];
                centreTilesCount++;
            }

            // As the factory no longer owns the tile, set its pointer to nullptr
            factory[i] = nullptr;
        }
    }  
}

std::string Factory::getTileString(){
    std::string tileString = "";
 
    if (hasTiles()){
    
        // Adds the characters of all the tiles into the array
        for (int i = 0; i < FACTORY_SIZE ; i++){

            char tileType = factory[i]->getType();
            tileType = toupper(tileType);
            std::string s(1, tileType);

            //get the type of tiles
            tileString += tileType;
        }
    }
    
    return tileString;
}