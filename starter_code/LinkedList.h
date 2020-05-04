#include "Node.h"

class LinkedList{
    public:
        LinkedList();
        ~LinkedList();
        int getSize();
        void insertFront(Tile tile);
        void insertBack(Tile tile);

    private:
        int size;
        Node* head;
};