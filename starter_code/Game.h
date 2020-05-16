
#ifndef AZUL_GAME
#define AZUL_GAME

#include "Player.h"
#include "Tile.h"
#include "LinkedList.h"
#include <string>
#include <vector>

#define FACTORY_SIZE    4
#define NUM_OF_FACTORIES  5

class Player;
class LinkedList;

class Game{
    public:
        // Constructor that initialises private values and sets players
        Game(std::vector<Player*> playersToAdd);

        // Load constructor
        Game (std::vector<Player*> playersToAdd, int playerCount, std::vector<Tile*> bag,
          int factoryCount, Tile*** factories, LinkedList* centreTable, std::vector<Tile*> boxLid,
          bool firstPlayerMarker);
        
        // Decontructor
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
        bool getTilesFromFactory(int factoryIndex, Types colour, int& tileAmount, Tile** tiles);
        
        // Removes the tiles of the inputted colour from the centre factory and places
        //   them into the inputted 'tiles' array
        // Returns true if first player marker has not been taken and remove
        //   the first player marker, otherwise false
        bool getTilesFromCentre(Types colour, int& tileAmount, Tile** tiles);
        
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
        std::string getCentreTable();

        //Returning string representation of tiles in factories
        std::string displayFactories();

        // Checks to see if at least one factory still contains tiles, including centre of the table
        // Returns true if at least one tile is present in a factory, else false
        bool checkIfFactoriesPopulated(Game* game);

    private:

        // Vector of all players
        std::vector<Player*> players;

        // Bag that holds tiles
        std::vector<Tile*> bag;

        // Amount of factories
        int factoryCount;

        // Two dimensional array for factories, with every row
        // being a different factory
        Tile*** factories;

        // The factory for the centre of the table
        LinkedList* centreTable;

        // Vector for the lid
        std::vector<Tile*> boxLid;

        // If true, then first player marker is still in the centre
        bool firstPlayerMarker;
};
#endif // AZUL_GAME
