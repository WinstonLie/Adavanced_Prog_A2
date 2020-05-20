#include "Bag.h"

Bag::Bag(){
    //constructor
    
}

Bag::Bag(std::vector<Tile*> otherBag){

    for(int i = 0 ; i < otherBag.size() ; i++){
        //Populating bag with copy
        bag.push_back(otherBag[i]);
    }
}

Bag::~Bag(){
    //destructor
    for (int i = 0 ; i < bag.size() ; i++){

        delete bag[i];
    }
}

void Bag::insertIntoBag(Tile* tile){
    bag.push_back(tile);
}

void Bag::removeFromBag(int value){
    //initializing temp
    Tile* tile = bag[value];

    //swap
    bag[value] = bag[bag.size() - 1];
    bag[bag.size() - 1] = tile;

    bag.pop_back();
}

int Bag::getSize(){
    return bag.size();
}

Tile* Bag::get(int index){
    Tile* tile = bag[index];
    return tile;
}