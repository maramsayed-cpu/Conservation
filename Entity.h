#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "Location.h"
#include "List.h"



class Entity{

    public:
        Entity(char c, int n, const Location& location);
        ~Entity();

        List* getSightingsHistory() const;
        Location* getLocation() const;

        void addSighting(const Sighting& s);
        int getNumSightings() const;
        void print() const;
        string getId() const;

    protected:
        string id;
        Location* location;

    private:
        List* sightingsHistory = new List();
        int tracker = 0;


};


#endif

