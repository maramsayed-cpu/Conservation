#include <iostream>
#include <string>

using namespace std;

#include "ResearcherList.h"

ResearcherList::ResearcherList(){
    head = NULL;
    tail = NULL;
    tracker = 0;
}

ResearcherList::~ResearcherList(){
    Node* currNode = head;
    Node* nextNode = NULL;

    clear();
    while(currNode!=NULL){
        nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }

}

void ResearcherList::add(const string& name, const Location& location){

    Node* newNode = new Node();

    newNode->data = new Researcher(name, location);
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


void ResearcherList::print() const{
    Node* currNode = head;
    cout<<"Print Researcher List..."<<endl;

    if (currNode == NULL){
        cout <<"Researcher List empty"<<endl;
    }

    while(currNode != NULL){
        currNode->data->print();
        cout <<endl;
        currNode = currNode->next;
    }
}


bool ResearcherList::isEmpty() const{
    return (tracker == 0);
}

Researcher* ResearcherList::removeFirst(){

    if (tracker == 0) { return nullptr;}

    Node* goner = head;

    head = head->next;
    
    if (head == nullptr) {
        tail = nullptr;
    }

    tracker--;
    Researcher* researcher = goner->data;
    delete goner->data;
    delete goner;
    return researcher;

}

Researcher* ResearcherList::get(int index) const{

    Node* currNode = head;
    for (int i = 0; i < index; i++){
        currNode = currNode->next;
    }
    return currNode->data;
}



void ResearcherList::clear(){

    Node* currNode = head;
    while(currNode != NULL){
        delete currNode->data;
        Node* goner = currNode;
        currNode = currNode->next;
        tracker--;
    }
}
