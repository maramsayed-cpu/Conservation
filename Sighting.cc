#include <iostream>
#include <string>

#include "Sighting.h"
#include "Researcher.h"


const string Sighting::animalTypes[] = {"Bird", "Mammal", "Reptile", "Amphibian", "Fish", "Insect", "Arachnid"};
const int Sighting::NUM_ANIMAL_TYPES = 7;

Sighting::Sighting(const Researcher& researcher, const string& animalType){
    this -> researcherId = researcher.getId();
    this -> animalType = animalType;
    
}

Sighting::Sighting(const string& researcherId, Location& location, const string& animalType){
    this -> researcherId = researcherId;
    this -> animalType = animalType;
    this -> location = location;
}

void Sighting::print() const{
    cout << "Researcher ID: " << researcherId << endl;
    cout << "Animal Type: " << animalType << endl;
    location.print();
}
string Sighting::getResearcherId() const{
    return researcherId;
}
const Location& Sighting::getLocation() const{
    return location;
}

string Sighting::getAnimalType() const{
    return animalType;
}
