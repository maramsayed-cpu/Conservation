#ifndef CONSERVATION_H
#define CONSERVATION_H

#include <string>

#include "ResearcherList.h"
#include "StationList.h"
#include "Sighting.h"
#include "Location.h"


class Conservation{

    public:
        Conservation();
        ~Conservation();

        void addResearcher(const string& name, const Location& location);
        void addStation(const Location& location);
        bool recordSighting(const Sighting& sighting);
        bool recordSighting(string researcherId, string animalType);
        bool moveResearcher(const string& id, const Location& location) const;
        bool getSightingsHistory(const string& id, const List*& sightings) const;
        void getSightingsOf(const string& animalType, List& outputList) const;
        void resetIds() const;
        void printStations() const;
        void printResearchers() const;
        Station* getStation(string id) const;
        Researcher* getResearcher(string id) const;

    private:
        StationList* stations;
        ResearcherList* researchers;
        int trackerR;
        int trackerS;


};


#endif