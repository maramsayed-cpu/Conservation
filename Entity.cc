#include <iostream>
#include <string>

using namespace std;

#include "Entity.h"


Entity::Entity(char c, int n, const Location& location){
    this -> id = c + to_string(n);
    this -> location = new Location(location);
}

Entity::~Entity(){
    delete sightingsHistory;
}

List* Entity::getSightingsHistory() const{
    return sightingsHistory;
}

Location* Entity::getLocation() const{
    return location;
}

void Entity::addSighting(const Sighting& s){

    sightingsHistory->add(s);
    tracker++;
}

int Entity::getNumSightings() const{
    return tracker;
}

string Entity::getId() const{
    return id;
}

void Entity::print() const{
    
    cout << "ID: " << id << endl;
    cout << "Number of Sightings: " << tracker << endl;
    location -> print();
    cout << endl;
}