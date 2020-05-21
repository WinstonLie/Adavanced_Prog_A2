#include "Tile.h"

Tile::Tile(Types type){
    this->type = type;
}

Tile::~Tile(){}

Types Tile::getType(){
    return this->type;
}

Types readTypeFromChar(char input){
    // Convert input to upper case
    input = std::toupper(input);
    // Initialises return value as invalid
    Types colour = Invalid;
    
    // Goes through the different types of tiles, sets colour to the
    // type that matches input if possible.
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
        colour = First_Player;
    }

    // Returns colour
    return colour;
}
