#include <iostream>
#include <string>

using namespace std;

#include "Station.h"

int Station::nextId = 0;

Station::Station(const Location& location): Entity(code, ++nextId, location) {};

Station::~Station(){
    delete location;
}

void Station::resetId(){
    Station::nextId = 0;
}

void Station::print() const{
    cout << "Station: " << endl;
    Entity::print();

}