#include "BoxLid.h"

BoxLid::BoxLid(){
    //constructor
}

BoxLid::BoxLid(std::vector<Tile*> boxLid) : boxLid{ boxLid }{}

BoxLid::~BoxLid(){
    //destructor
}

void BoxLid::insertIntoBoxLid(Tile* tile){
    boxLid.push_back(tile);
}

void BoxLid::removeFromBoxLid(int value){
    boxLid.erase(boxLid.begin() + value);
}

int BoxLid::getSize(){
    int size = boxLid.size();
    return size;
}

Tile* BoxLid::get(int index){
    Tile* tile = boxLid[index];
    return tile;
}