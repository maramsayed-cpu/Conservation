#ifndef SIGHTING_H
#define SIGHTING_H

#include <iostream>
#include <string>

#include "Location.h"

using namespace std;

class Researcher;

class Sighting {

    public:

        static const string animalTypes[];
        static const int NUM_ANIMAL_TYPES;

        Sighting(const Researcher& researcher, const string& animalType);
        Sighting(const string& researcherId, Location& location, const string& animalType);

        void print() const;
        string getResearcherId() const;
        const Location& getLocation() const;
        string getAnimalType() const;

    private:
        string researcherId;
        string animalType = "Bird";
        Location location;
};

#endif