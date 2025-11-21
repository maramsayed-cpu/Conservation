#ifndef LIST_H
#define LIST_H
#include <string>

#include "Sighting.h"

class List{

    class Node {


        public:
            Sighting* data;
            Node*    next;
    };

    public:
        List();
        ~List();

        bool isEmpty() const;
        int getSize() const;
        Sighting* removeFirst();
        void add(const Sighting& sighting);
        void print() const;
        void getSightingsOf(const string& animalType, List& outputList);
        void removeSightingsOf(const string& animalType, List& outputList);
        void clear();



    private:
        Node* head;
        Node* tail;
        int tracker = 0;

};


#endif

