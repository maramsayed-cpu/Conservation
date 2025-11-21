#include <iostream>
#include <string>

using namespace std;

#include "Researcher.h"


int Researcher::nextId = 0;

Researcher::Researcher(const string& name, const Location& location): name(name), Entity(code, ++nextId, location){};

Researcher::~Researcher() {
    delete location;
}

void Researcher::resetId(){
    Researcher::nextId = 0;
}

void Researcher::setLocation(const Location& location){
    *(this -> location) = location;
}

void Researcher::print() const{
    cout << "Researcher Name: " << name << endl;
    Entity::print();

}