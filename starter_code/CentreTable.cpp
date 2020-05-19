#include "CentreTable.h"

CentreTable::CentreTable(){
    head = nullptr;
}

CentreTable::CentreTable(std::vector<Tile*> centreTable){
    head = nullptr;
    // Inserts tile pointers from vector, put them into linked list
    for (int i = 0; i < centreTable.size(); i++){
        insert(centreTable[i]);
    }
}

CentreTable::~CentreTable(){
    //destructor
}

int CentreTable::getSize(){
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

void CentreTable::insert(Tile* tile){
    Node* newNode = new Node(tile);
    newNode->setNext(head);
    head = newNode;
}

void CentreTable::removeTiles(Types colour, Tile**& tiles, int& tileCount){
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
        }
        // If the node was not deleted, then move on to next node
        if (iterator != nullptr){
            previous = iterator;
            iterator = iterator->getNext();
        // If node was deleted,
        } else {
            // If there is a previous node, set the new current node to the new next node
            if (previous != nullptr){
                iterator = previous->getNext();
            // If there is no previous node, set current to head
            } else {
                iterator = head;
            }
        }

    }
    
}

void CentreTable::clear(){
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

void CentreTable::removeNode(Node* prevNode, Node*& nodeToDel){
    //if the head
    if(prevNode == nullptr && nodeToDel != nullptr){
        head = nodeToDel->getNext();
        nodeToDel->setTile(nullptr);
        delete nodeToDel;
        nodeToDel = nullptr;
    }
    //if any other node
    else if(prevNode != nullptr && nodeToDel != nullptr){
        prevNode->setNext(nodeToDel->getNext());
        nodeToDel->setTile(nullptr);
        delete nodeToDel;
        nodeToDel = nullptr;
    }
}

std::string CentreTable::getCenterTableDetails(){
    Node* iterator = head;
    std::string data = "";

    while(iterator != nullptr){
    data += iterator->getTileFromNode()->getType();
    iterator = iterator->getNext();
    }
    
    data += "$";
    return data;
}
std::string CentreTable::getTilesFromCenterTable(){
    Node* iterator = head;
    std::string tilesInCenterTable = "";
    while(iterator != nullptr){
        char type = iterator->getTileFromNode()->getType();
        type = toupper(type);
        std::string s(1, type);
        tilesInCenterTable += s + " ";
        iterator = iterator->getNext();
    }

    return tilesInCenterTable;
}


