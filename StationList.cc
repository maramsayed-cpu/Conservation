#include <iostream>
#include <string>

using namespace std;

#include "StationList.h"

StationList::StationList(){
    head = NULL;
    tail = NULL;
    tracker = 0;
}

StationList::~StationList(){
    Node* currNode = head;
    Node* nextNode = NULL;

    clear();
    while(currNode!=NULL){
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }

}

void StationList::add(const Location& location){


    Node* newNode = new Node();

    newNode->data = new Station(location);
    
    newNode->next = NULL;

    if (tracker == 0){
        head = tail = newNode;
    }
    
    else {
        tail->next = newNode;
        tail = newNode;
    }

    tracker++;

}


void StationList::print() const{
    Node* currNode = head;
    cout<<"Print Station List..."<<endl;

    if (currNode == NULL){
        cout <<"Station List empty"<<endl;
    }

    while(currNode != NULL){
        currNode->data->print();
        cout <<endl;
        currNode = currNode->next;
    }
}


bool StationList::isEmpty() const{
    return (tracker == 0);
}

Station* StationList::removeFirst(){

    if (tracker == 0) { return nullptr;}

    Node* goner = head;

    head = head->next;
    
    if (head == nullptr) {
        tail = nullptr;
    }

    tracker--;
    Station* station = goner->data;
    delete goner->data;
    delete goner;
    return station;

}

Station* StationList::get(int index) const{

    Node* currNode = head;
    for (int i = 0; i < index; i++){
        currNode = currNode->next;
    }
    return currNode->data;
}



void StationList::clear(){

    Node* currNode = head;
    while(currNode != NULL){
        delete currNode->data;
        Node* goner = currNode;
        currNode = currNode->next;
        tracker--;
    }
}