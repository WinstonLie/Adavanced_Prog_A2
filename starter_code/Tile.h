#ifndef AZUL_TILES
#define AZUL_TILES

#include <string>

enum Types {
            Red = 'R',
            Yellow = 'Y',
            Dark_Blue = 'B',
            Light_Blue = 'L',
            Black = 'U',
            starter_player = 'F',
            Empty = '.',
            Invalid = '_'
        };

class Tile{
    public:
        Tile();
        Tile(Types type);
        ~Tile();
        Types getType();

    private:
        Types type;
};

Types readTypeFromChar(char input);

#endif //AZUL_TILES