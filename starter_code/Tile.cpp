#include "Tile.h"

Tile::Tile(Types type){
    this->type = type;
}

Tile::~Tile(){
    //destructor
}

Types Tile::getType(){
    return this->type;
}

// May potentially be moved to a util file for use in main program
Types readTypeFromChar(char input){
    input = std::toupper(input);
    Types colour = Invalid;
    if (input == 'R'){
        colour = Red;
    } else if (input == 'Y'){
        colour = Yellow;
    } else if (input == 'B'){
        colour = Dark_Blue;
    } else if (input == 'L'){
        colour = Light_Blue;
    } else if (input == 'U') {
        colour = Black;
    } else if (input == '.'){
        colour = Empty;  
    } else if (input == 'F'){
        colour = starter_player;
    }

    return colour;
}
