
#ifndef AZUL_GAME
#define AZUL_GAME

#include "Player.h"
#include "Tile.h"
#include "CentreTable.h"
#include "Bag.h"
#include "BoxLid.h"
#include "Factory.h"
#include <string>



//#define NUM_OF_FACTORIES  5
#define DEFAULT_SEED      100
#define TILES_PER_COLOUR  20

// Forward declarations for player
class Player;

// Class game holds all data that relates to the game
// Doesn't handle players taking turns, doesn't contain current player
// Driver for this class is PlayGame
class Game{
    public:

        // Constructor that initialises private values and sets players
        // Also creates all tiles needed for game
        Game(std::vector<Player*> playersToAdd, bool twoCentreTables, int randomSeed = DEFAULT_SEED);

        // Load constructor
        Game (std::vector<Player*> playersToAdd, int playerCount, Bag* bag,
          int factoryCount, Factory** factories, CentreTable* centreTable, BoxLid* boxLid,
          bool firstPlayerMarker, int randomSeed = DEFAULT_SEED);
        
        // Decontructor, deletes all tiles in all sub-containers
        ~Game();
        
        // Moves tiles from the lid into the bag
        void populateBagFromLid();
        
        // Fills up the factories with tiles from the bag
        void populateFactories();
        
        // Returns the amount of players
        int getPlayerCount();
        
        // Returns the player at the specified index, or nullptr if not present
        Player* getPlayer(int index);
        
        // Removes the tiles of the inputted colour from the specified factory and places
        //   them into the inputted 'tiles' array
        // Returns true if factory was emptied, else false
        bool getTilesFromFactory(int factoryIndex, Types colour, int& tileAmount, Tile**& tiles, int centreTableIndex);
        
        // Removes the tiles of the inputted colour from the centre factory and places
        //   them into the inputted 'tiles' array
        // Returns true if first player marker has not been taken and remove
        //   the first player marker, otherwise false
        bool getTilesFromCentre(Types colour, int& tileAmount, Tile**& tiles, int indexOfCentreTable = 0);
        
        // Returns true if the first player marker has been taken, otherwise false
        bool isFirstPlayerMarkerTaken();

        // Adds a tile to the box lid
        void addToBoxLid(Tile* tile);

        //get bag data for saving
        std::string getBag();

        //get boxLid data for saving
        std::string getBoxLid();

        //get factory data for saving
        std::string getFactories();

        //get centreTable data for saving
        std::string getCentreTable(int indexOfCentreTable);

        //Returning string representation of tiles in factories
        std::string displayFactories();

        // Checks to see if at least one factory still contains tiles, including centre of the table
        // Returns true if at least one tile is present in a factory, else false
        bool checkIfFactoriesPopulated();

        // Returns the random seed being used for game
        int getRandomSeed();

        //get all the turn commands
        std::string getCommands();

        //add turn command into commands
        void addCommand(std::string command);

        //get all the turn commands
        std::string getCommandsForEndSave();

        //add turn command into commands
        void addCommandToEndSave(std::string command);

        std::string getSingleCommand(int i);

        int getNumOfFactories();

        int getNumOfCentreTable();

    private:

        std::vector<std::string> commands;

        std::vector<std::string> commandsForEndSave;

        // Vector of all players
        std::vector<Player*> players;

        // Bag that holds tiles
        Bag* bag;

        // Amount of factories
        int factoryCount;

        // Two dimensional array for factories, with every row
        // being a different factory
        // Tile*** factories;

        // The factory for the centre of the table
        CentreTable* centreTable;

        //Storage of Centre Table's
        std::vector<CentreTable*> centreTables;

        // Vector for the lid
        BoxLid* boxLid;

        // If true, then first player marker is still in the centre
        bool firstPlayerMarker;

        // Seed for the random number generator
        int randomSeed;

        // Array of pointers to factories
        Factory** factories;

        int NUM_OF_FACTORIES;
};
#endif // AZUL_GAME
