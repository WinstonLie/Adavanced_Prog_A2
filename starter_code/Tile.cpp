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
