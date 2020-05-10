#include "Tile.h"

Tile::Tile(Types* type){
    this->type = type;
}

Tile::~Tile(){
    this->type = nullptr;
}

Types* Tile::getType(){
    return this->type;
}
