#include "Node.h"

Node::Node(Tile* tile){
    this->tile = tile;
    this->nextNode = nullptr;
}

Node::~Node(){
   this->nextNode = nullptr;
}

void Node::setNext(Node* node){
    this->nextNode = node;
}

Node* Node::getNext(){
    return this->nextNode;
}

Tile* Node::getTileFromNode(){
    return this->tile;
}

