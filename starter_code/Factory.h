#ifndef AZUL_FACTORY
#define AZUL_FACTORY

#include "Tile.h"

#define FACTORY_SIZE      4

class Factory{
    public:

        // Default constructer, creates empty factory
        Factory();

        // Deconstructor
        ~Factory();

        // Constructs the factory with the inputted tile array
        // Assumes array is of the expected length (FACTORY_SIZE)
        Factory(Tile** tiles);

        // Returns true if the factory contains any tiles, else false
        bool hasTiles();

        // Returns true if a tile with the colour inserted is contained in factory
        // , else false
        bool hasColour(Types colour);

        // Sets the tiles inputted, if the tiles dont match the capacity of the
        //  factory return false, else true
        bool setTiles(Tile** tiles, int tileCount);
        
        // Gets the tiles of the specified colour and puts them inside the tiles array,
        //   and gets the rest and puts them into the centreTiles, to put into the centre table by game
        // If tileCount == 0, then nothing is cleared, else the factory is emptied
        // Assumes inputted references are either nullptr or undefined
        void getTiles(Types colour, Tile**& tiles, int& tileCount, Tile**& centreTiles, int& centreTilesCount);

        // Converts the tiles in the array into characters then puts it into the character array reference
        // If empty, then tileChars is nullptr
        // Used for printing the tiles as characters
        std::string getTileString();

        // Returns the max value for a factory
        int getSizeMax();
    private:
        // Array of tiles inside the factory
        Tile** factory;

};

#endif //AZUL_FACTORY