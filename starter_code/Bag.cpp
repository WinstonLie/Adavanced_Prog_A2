#include "Bag.h"

Bag::Bag(){}

Bag::Bag(std::vector<Tile*> otherBag){

    for(int i = 0 ; i < otherBag.size() ; i++){
        //Populating bag with copy
        bag.push_back(otherBag[i]);
    }
}

Bag::~Bag(){
    //destructor, deletes all tiles in bag
    for (int i = 0 ; i < bag.size() ; i++){

        delete bag[i];
    }
}

void Bag::insertIntoBag(Tile* tile){
    bag.push_back(tile);
}

void Bag::removeFromBag(int index){
    //initializing temp pointer
    Tile* tile = bag[index];

    // Swap tile to delete with last element
    bag[index] = bag[bag.size() - 1];
    bag[bag.size() - 1] = tile;

    // Delete last element
    bag.pop_back();
}

int Bag::getSize(){
    return bag.size();
}

Tile* Bag::get(int index){
    Tile* tile = bag[index];
    return tile;
}