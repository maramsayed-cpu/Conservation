
#include "Control.h"
#include <limits>
#include <vector>

using namespace std;
#define NUM_STATIONS 5
#define NUM_RESEARCHERS 5

extern const string names[NUM_RESEARCHERS];



void Control::launch(){

    vector<string> menu ={
        "Print stations",
        "Print researchers",
        "Add station",
        "Add researcher", 
        "Record sighting",
        "Print sightings recorded at station",
        "Print sightings recorded by researcher",
        "Print sightings of animal type",
        "Move researcher"
    };

    init();
    int choice = -1;

    while (choice!= 0){
        view.menu(menu, choice);
        switch(choice){
            case 1: printStations(); break;
            case 2: printResearchers(); break;
            case 3: addStation(); break;
            case 4: addResearcher(); break;
            case 5: recordSighting(); break;
            case 6: printStationSightings(); break;
            case 7: printResearcherSightings(); break;
            case 8: printSightingsOf(); break;
            case 9: moveResearcher(); break;
        }
    }
    cout<<"exiting program!!!"<<endl;
}

void Control::init(){
    cout<<"Initializing cells and stations..."<<endl;
    for (int i = 0; i < NUM_STATIONS; ++i){
        conservation.addStation(Location(rand()%100, rand()%100));
    }
    for (int i = 0; i < NUM_RESEARCHERS; ++i){
        conservation.addResearcher(names[i], Location(rand()%100, rand()%100));
    }
    cout<<"All entities initialized!"<<endl;
}

void Control::addStation(){
    cout<<"Adding station..."<<endl;
    int x, y;
    view.getLocation(x, y);
    conservation.addStation(Location(x, y));
    cout<<"Station added!"<<endl;
}

void Control::printStations(){
    cout<<"Printing stations..."<<endl;
    conservation.printStations();
}

void Control::printResearchers(){
    cout<<"Printing researchers..."<<endl;
    conservation.printResearchers();
}


void Control::addR(string& id){
    if (id.find('R') == string::npos){
        id = "R" + id;
    }
}

void Control::addS(string& id){
    if (id.find('S') == string::npos){
        id = "S" + id;
    }
}



void Control::addResearcher(){
    cout<<"Adding researcher...\nPlease enter name:"<<endl;
    string name;
    view.getString(name);
    int x, y;
    view.getLocation(x, y);
    conservation.addResearcher(name, Location(x, y));
}


void Control::recordSighting(){
    cout<<"Recording sighting..."<<endl;
    string id, receiver, sighting;
    printResearchers();
    cout<<"Please enter researcher id:"<<endl;
    view.getString(id);
    addR(id);

    Researcher* r = conservation.getResearcher(id);
    if (r == nullptr){  
        cout<<"Researcher not found!"<<endl;
        return;
    }
    cout<<"Please enter animal sighted:"<<endl;

    int choice = 0;
    view.menu(Sighting::animalTypes, Sighting::NUM_ANIMAL_TYPES, choice);
    if (choice == 0){
        return;
    }
    --choice;
    conservation.recordSighting(id, Sighting::animalTypes[choice]);
}

void Control::printStationSightings(){
    cout<<"Printing station sightings..."<<endl;
    string id;
    conservation.printStations();
    cout<<"Please enter station id:"<<endl;
    view.getString(id);
    addS(id);
    cout<<"Printing sighting history for: "<<id<<endl;
    const List* l;
    if (conservation.getSightingsHistory(id, l)){
        view.printList(*l);
    }else{
        cout<<"Station not found!"<<endl;
    }
}

void Control::printResearcherSightings(){
    string id;
    conservation.printResearchers();
    cout<<"Please enter researcher id: "<<endl;
    view.getString(id);
    addR(id);
    cout<<"Printing sighting history for: "<<id<<endl;
    const List* l;
    if (conservation.getSightingsHistory(id, l)){
        view.printList(*l);
    }else{
        cout<<"Researcher not found!"<<endl;
    }
}

void Control::printSightingsOf(){
    cout<<"Printing sightings of animal type..."<<endl;
    int choice = 0;
    cout<<"Please enter animal type: "<<endl;
    view.menu(Sighting::animalTypes, Sighting::NUM_ANIMAL_TYPES, choice);
    if (choice == 0){
        return;
    }
    --choice;
    List sightings;
    conservation.getSightingsOf(Sighting::animalTypes[choice], sightings);
    cout<<"Sightings of animal type: "<<Sighting::animalTypes[choice]<<endl;
    view.printList(sightings);
}


void Control::moveResearcher(){
    string id;
    printResearchers();
    cout<<"Please enter the researcher id: "<<endl;
    view.getString(id);
    addR(id);
    cout<<"Moving researcher: "<<id<<endl;
    int x, y;
    view.getLocation(x, y);
    conservation.moveResearcher(id, Location(x, y));
}


const string names[NUM_RESEARCHERS] = {
    "Alice",
    "Bob",
    "Charlie",
    "Diana",
    "Ethan"
};

