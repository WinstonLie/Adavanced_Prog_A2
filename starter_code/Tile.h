#ifndef AZUL_TILES
#define AZUL_TILES

#include <string>

// Enum that represents the different tiles that can exist
enum Types {
            Red = 'R',
            Yellow = 'Y',
            Dark_Blue = 'B',
            Light_Blue = 'L',
            Black = 'U',
            First_Player = 'F',
            Empty = '.',
            Invalid = '_'
        };

// Class Tile holds the type of a tile that exists on the board. Most the tiles
// are created during the creation of the game, and aren't deleted until the game
// itself is. The exception to this is the first player marker, which is created
// when a player recieves one and deleted from the penalty line of the player when
// it gets emptied.
class Tile{
    public:
        // Constructor that accepts the type of the tile
        Tile(Types type);

        // Deconstructer, does nothing
        ~Tile();

        // Returns the type of the tile
        Types getType();

    private:
        // The type of the tile
        Types type;
};

// Utulity function that parses a character into a type of tile,
// and returns it. If not a valid char, Invalid is returned
Types readTypeFromChar(char input);

#endif //AZUL_TILES