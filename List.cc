#include <iostream>
#include <string>

using namespace std;

#include "List.h"

List::List(){
    head = NULL;
    tail = NULL;
}

List::~List(){

    Node* currNode = head;
    Node* nextNode = NULL;

    
    while(currNode!=NULL){
        nextNode = currNode->next;
        delete currNode->data;
        delete currNode;
        currNode = nextNode;
    }


}

void List::add(const Sighting& sighting) {
    Node* newNode = new Node();
    newNode->data = new Sighting(sighting);
    
    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    tracker++;

}


void List::print() const{
    Node* currNode = head;
    cout<<"Print list..."<<endl;

    if (currNode == NULL){
        cout <<"List empty"<<endl;
    }

    while(currNode != NULL){
        currNode->data->print();
        cout <<endl;
        currNode = currNode->next;
    }
}


bool List::isEmpty() const{
    return (tracker == 0);
}

int List::getSize() const{
    return tracker;
}

Sighting* List::removeFirst(){

    if (tracker == 0) { return nullptr;}

    Node* goner = head;

    head = head->next;
    
    if (head == nullptr) {
        tail = nullptr;
    }

    Sighting* sighting = goner->data;
    delete goner;
    tracker--;
    return sighting;

}

void List::getSightingsOf(const string& animalType, List& outputList){
    Node* currNode = head;
    
    while(currNode != NULL){
        if((currNode->data->getAnimalType()).compare(animalType) == 0){
            outputList.add(*(currNode->data));
            (*(currNode->data)).print();
        }
        currNode = currNode->next;
    }
    
}

void List::removeSightingsOf(const string& animalType, List& outputList){
    Node* currNode = head;
    Node* prevNode = NULL;

    while(currNode != NULL){
        if(currNode->data->getAnimalType() == animalType){
            outputList.add((*(currNode->data)));

            Node* goner = currNode;
            currNode = currNode->next;
            prevNode->next = currNode;
            tracker--;
            delete goner->data;
            delete goner;
        }
        else {
            prevNode = currNode;
            currNode = currNode->next;
        }
    }
}

void List::clear(){

    Node* currNode = head;
    Node* nextNode = NULL;

    
    while(currNode!=NULL){
        nextNode = currNode->next;
        delete currNode->data;
        delete currNode;
        currNode = nextNode;
        tracker--;
    }

    
}

