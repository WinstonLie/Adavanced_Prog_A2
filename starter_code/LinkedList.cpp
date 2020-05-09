#include "LinkedList.h"

LinkedList::LinkedList(){
    head = nullptr;
}

LinkedList::~LinkedList(){
    //destructor
}

int LinkedList::getSize(){
    int count = 0;
    bool hasNext = true;
    Node* current = head;
    //Check to see if there are still nodes in the linked list
    while(hasNext == true){
        if(current != nullptr){
            count++;
            current =  current->getNext();
        }else{
            hasNext = false;
        }
    }

    return count;
}

void LinkedList::insert(Tile* tile){
    Node* newNode = new Node(tile);
    newNode->setNext(head);
    head = newNode;
}

void LinkedList::removeTiles(Types colour, Tile** tiles, int& tileCount){
    
}

void LinkedList::clear(){
    
}


