#include "Bag.h"

Bag::Bag(){
    //constructor
    
}

Bag::Bag(std::vector<Tile*> otherBag): bag{ bag }{}

Bag::~Bag(){
    //destructor
}

void Bag::insertIntoBag(Tile* tile){
    bag.push_back(tile);
}

void Bag::removeFromBag(int value){
    bag.erase(bag.begin() + value);
}

int Bag::getSize(){
    return bag.size();
}

Tile* Bag::get(int index){
    Tile* tile = bag[index];
    return tile;
}