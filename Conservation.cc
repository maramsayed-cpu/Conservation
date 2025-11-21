#include <iostream>
#include <string>

using namespace std;

#include "Conservation.h"

Conservation::Conservation()
{
    stations = new StationList();
    researchers = new ResearcherList();
    trackerS = 0;
    trackerR = 0;
}

Conservation::~Conservation()
{
    delete stations;
    delete researchers;
}

void Conservation::addResearcher(const string &name, const Location &location)
{

    researchers->add(name, location);
    trackerR++;
}

void Conservation::addStation(const Location &location)
{

    stations->add(location);
    trackerS++;
}

bool Conservation::recordSighting(const Sighting &sighting)
{

    for (int i = 0; i < trackerR; i++)
    {
        if (researchers->get(i)->getId() == sighting.getResearcherId())
        {
            researchers->get(i)->addSighting(sighting);

            Researcher *researcher = researchers->get(i);

            Station *closest = stations->get(0);
            for (int j = 1; j < trackerS; j++)
            {
                if (stations->get(j)->getLocation()->getDistance(*(researcher->getLocation())) < closest->getLocation()->getDistance(*(researcher->getLocation())))
                {
                    closest = stations->get(j);
                }
            }

            closest->addSighting(sighting);
            return true;
        }
    }
    return false;
}

bool Conservation::recordSighting(string researcherId, string animalType)
{

    for (int i = 0; i < trackerR; i++)
    {
        if (researchers->get(i)->getId() == researcherId)
        {
            Sighting addition = Sighting(researcherId, *(researchers->get(i)->getLocation()), animalType);
            researchers->get(i)->addSighting(addition);

            Researcher *researcher = researchers->get(i);

            Station *closest = stations->get(0);
            for (int j = 1; j < trackerS; j++)
            {
                if (stations->get(j)->getLocation()->getDistance(*(researcher->getLocation())) < closest->getLocation()->getDistance(*(researcher->getLocation())))
                {
                    closest = stations->get(j);
                }
            }

            closest->addSighting(addition);
            return true;
        }
    }
    return false;
}
bool Conservation::moveResearcher(const string &id, const Location &location) const
{

    for (int i = 0; i < trackerR; i++)
    {
        if (researchers->get(i)->getId() == id)
        {
            researchers->get(i)->setLocation(location);
            return true;
        }
    }
    cout << "Could not find researcher." << endl;
    return false;
}
bool Conservation::getSightingsHistory(const string &id, const List *&sightings) const
{
    for (int i = 0; i < trackerR; i++)
    {
        if (researchers->get(i)->getId() == id)
        {
            sightings = researchers->get(i)->getSightingsHistory();
            return true;
        }
    }
    for (int i = 0; i < trackerS; i++)
    {
        if (stations->get(i)->getId() == id)
        {
            sightings = stations->get(i)->getSightingsHistory();
            return true;
        }
    }
    return false;
}
void Conservation::getSightingsOf(const string &animalType, List &outputList) const
{

    for (int i = 0; i < trackerS; i++)
    {

        stations->get(i)->getSightingsHistory()->getSightingsOf(animalType, outputList);
    }
}

void Conservation::resetIds() const
{
    Researcher::resetId();
    Station::resetId();
}
void Conservation::printStations() const
{
    cout << "Printing all Stations..." << endl
         << endl;

    for (int i = 0; i < trackerS; i++)
    {
        stations->get(i)->print();
    }
}
void Conservation::printResearchers() const
{
    cout << "Printing all Researchers..." << endl
         << endl;

    for (int i = 0; i < trackerR; i++)
    {
        researchers->get(i)->print();
    }
}
Station *Conservation::getStation(string id) const
{
    for (int i = 0; i < trackerS; i++)
    {
        if (stations->get(i)->getId() == id)
        {
            return stations->get(i);
        }
    }
    return nullptr;
}
Researcher *Conservation::getResearcher(string id) const
{
    for (int i = 0; i < trackerR; i++)
    {
        if (researchers->get(i)->getId() == id)
        {
            return researchers->get(i);
        }
    }
    return nullptr;
}