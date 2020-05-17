#include "LinkedList.h"
// #include "Game.h"

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

void LinkedList::removeTiles(Types colour, Tile**& tiles, int& tileCount){
    Node* iterator = head;
    Node* previous = nullptr;
    while(iterator != nullptr){
        //check if next node matches the color
        if(iterator->getTileFromNode()->getType() == colour){
            //put into array
            tiles[tileCount] = iterator->getTileFromNode();
            tileCount++;
            //remove tile that matches the colour
            removeNode(previous, iterator);
            if (iterator == nullptr){
                iterator = head;
            }
        }
        previous = iterator;
        iterator = iterator->getNext();

    }
    
}

void LinkedList::clear(){
    Node* iterator = head;
    Node* iteratorNext = nullptr;
    
    while(iterator->getNext() != nullptr){
        
    }

    //delete all the nodes
    iterator = head;
    while(iterator != nullptr){
        //insert tiles into the box lid
        game->addToBoxLid(iterator->getTileFromNode());
        //deallocate memory
        iteratorNext = iterator->getNext();
        iterator->setTile(nullptr);
        delete iterator;
        iterator = iteratorNext;
   }
   
}

void LinkedList::removeNode(Node* prevNode, Node* nodeToDel){
    //if the head
    if(prevNode == nullptr && nodeToDel != nullptr){
        head = nodeToDel->getNext();
        nodeToDel->setTile(nullptr);
        delete nodeToDel;
    }
    //if any other node
    else if(prevNode != nullptr && nodeToDel != nullptr){
        prevNode->setNext(nodeToDel->getNext());
        nodeToDel->setTile(nullptr);
        delete nodeToDel;
    }
}

std::string LinkedList::getCenterTableDetails(){
    Node* iterator = head;
    std::string data = "";

    while(iterator != nullptr){
    data += iterator->getTileFromNode()->getType();
    iterator = iterator->getNext();
    }
    
    data += "$";
    return data;
}
std::string LinkedList::getTilesFromCenterTable(){
    Node* iterator = head;
    std::string tilesInCenterTable = "";
    while(iterator != nullptr){
        tilesInCenterTable += std::toupper(iterator->getTileFromNode()->getType());
        iterator = iterator->getNext();
    }

    return tilesInCenterTable;
}


