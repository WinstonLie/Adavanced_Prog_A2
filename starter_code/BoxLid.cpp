#include "BoxLid.h"

BoxLid::BoxLid(){
    //constructor
}

BoxLid::BoxLid(std::vector<Tile*> otherBoxLid){
    for(int i = 0 ; i < otherBoxLid.size() ; i++){
        //Populating box lid with copy
        boxLid.push_back(otherBoxLid[i]);
    }
}

BoxLid::~BoxLid(){
    //destructor
    for (int i = 0 ; i < boxLid.size() ; i++){

    delete boxLid[i];
}
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