
#include "TestControl.h"
#include "Conservation.h"
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;
#define NUM_STATIONS 5
#define NUM_RESEARCHERS 5

const string researchers[NUM_RESEARCHERS] = {"Fred", "Daphne", "Velma", "Shaggy", "Scooby"};


void TestControl::launch(){

    vector<string> menu ={
        "Test add and print Stations",
        "Test add and print Researchers",
        "Test record sighting",
        "Test print sightings at Station",
        "Test print sightings from Researcher",
        "Test print sightings of animal",
        "Test move Researcher",
        "Test all and get mark"
    };

    int choice = -1;

    while (choice!= 0){
        view.menu(menu, choice);
        switch(choice){
            case 1: testAddStations(); break;
            case 2: testAddResearchers(); break;
            case 3: testRecordSighting(); break;
            case 4: testPrintStationSightings(); break;
            case 5: testPrintResearcherSightings(); break;
            case 6: testPrintSightingsOfAnimal(); break;
            case 7: testMoveResearcher(); break;
            case 8: int mark = testAddStations();
                    mark+= testAddResearchers();
                    mark+= testPrintStationSightings();
                    mark+= testPrintResearcherSightings();
                    mark+= testPrintSightingsOfAnimal();
                    mark+= testRecordSighting();
                    mark+= testMoveResearcher();

                    cout<<"Total marks: "<<mark<<"/16"<<endl;
                    
                    break;
        }
    }
    std::cout<<"exiting program!!!"<<endl;
}

void TestControl::initStations(Conservation& conservation, Location* locations, int numStations){
    cout<<"Initializing stations..."<<endl;
    for (int i = 0; i < numStations; ++i){
        conservation.addStation(locations[i]);
        
    }
    cout<<"Stations initialized!"<<endl;
}

void TestControl::initResearchers(Conservation& conservation, Location* locations, int numResearchers){
    cout<<"Initializing researchers..."<<endl;
    
    for (int i = 0; i < numResearchers; ++i){
        conservation.addResearcher(researchers[i], locations[i]);
    }
    cout<<"Researchers initialized!"<<endl;
}

int TestControl::testAddStations(){
    int marks = 2;
    Conservation conservation;
    conservation.resetIds();
    cout<<"1. Test add and print stations"<<endl;
    
    // generate and store random locations
    Location locations[NUM_STATIONS];
    string loc[NUM_STATIONS];
    for (int i = 0; i < NUM_STATIONS; ++i){
        locations[i] = Location(rand()%100, rand()%100);
        tester.initCapture();
        locations[i].print();
        tester.endCapture();
        loc[i] = tester.getOutput();
    }
    
    initStations(conservation, locations, NUM_STATIONS);

    
    cout<<"Printing stations..."<<endl;
    tester.initCapture();
    conservation.printStations();
    tester.endCapture();

    int error = 0;
    tester.find({0,1,2,3,4}, loc, error);

    if (error>0){
        cout<<error<<" locations not found, test failed, -1"<<endl;
        cout<<"Station print should print location data"<<endl;
        marks -= 1;
    }else{

        cout<<"All locations found"<<endl<<endl;
    }

    string labels[NUM_STATIONS] = {"S1", "S2", "S3", "S4", "S5"};
    tester.find({0,1,2,3,4}, labels, error);
    if (error>0){
        cout<<error<<" labels not found, test failed"<<endl;
        marks -= 1;
    }else{
        cout<<"All labels found"<<endl<<endl;
    }
    cout<<"Test complete, marks: "<<marks<<endl;
    
    return marks;

}


int TestControl::testAddResearchers(){
    int marks = 2;
    Conservation conservation;
    conservation.resetIds();
    cout<<"2. Test add and print researchers"<<endl;

    // generate and store random locations
    Location locations[NUM_RESEARCHERS];
    string loc[NUM_RESEARCHERS];
    for (int i = 0; i < NUM_RESEARCHERS; ++i){
        locations[i] = Location(rand()%100, rand()%100);
        tester.initCapture();
        locations[i].print();
        tester.endCapture();
        loc[i] = tester.getOutput();
    }
    initResearchers(conservation, locations, NUM_RESEARCHERS);

    cout<<"Printing researchers..."<<endl;
    tester.initCapture();
    conservation.printResearchers();
    tester.endCapture();

    int error = 0;
    tester.find({0,1,2,3,4}, loc, error);

    if (error>0){
        cout<<error<<" locations not found, test failed, -1"<<endl;
        cout<<"Researcher print should print location data"<<endl;
        marks -= 1;
    }else{

        cout<<"All locations found"<<endl<<endl;
    }

    string labels[NUM_RESEARCHERS] = {"R1", "R2", "R3", "R4", "R5"};
    tester.find({0,1,2,3,4}, labels, error);
    if (error>0){
        cout<<error<<" labels not found, test failed"<<endl;
        marks -= 1;
    }else{
        cout<<"All labels found"<<endl<<endl;
    }
    cout<<"Test complete, marks: "<<marks<<endl;
    return marks;
}

int TestControl::testRecordSighting(){
    Location tLocs[NUM_STATIONS]={Location(0,0), Location(5,5), Location(10,10), Location(15,15), Location(20,20)};
    Location cLocs[NUM_RESEARCHERS] = {Location(1,1), Location(4,6), Location(8,12), Location(19,21), Location(25,25)};
    Location sLocs[10] = {Location(2,2), Location(6,5), Location(9,11), Location(16,16), Location(18,22), Location(26,24), Location(3,3), Location(5,7), Location(12,10), Location(21,19)};
    Conservation conservation;
    conservation.resetIds();
    cout<<"3. Test record sighting"<<endl<<endl;
    cout<<"We are adding researchers and stations to a conservation, then recording Sightings. ";
    cout<<"When a sighting is recorded, it should be added to the researcher, and to the nearest station."<<endl;

    int mark1 = 2;
    int mark2 = 2;
    int marks = 0;

    initStations(conservation, tLocs, NUM_STATIONS);
    initResearchers(conservation, cLocs, NUM_RESEARCHERS);

    const string researcherIds[NUM_RESEARCHERS] = {"R1", "R2", "R3", "R4", "R5"};
    Researcher* r[NUM_RESEARCHERS];
    cout<<"Reading Researchers into an array"<<endl<<endl;

    for (int i = 0; i < NUM_RESEARCHERS; ++i){  
        r[i] = conservation.getResearcher(researcherIds[i]);
    }
    const int numSightings = 9;
    Sighting s[numSightings] = {
        Sighting(*r[0], Sighting::animalTypes[0]),
        Sighting(*r[1], Sighting::animalTypes[1]),
        Sighting(*r[0], Sighting::animalTypes[0]),
        Sighting(*r[1], Sighting::animalTypes[1]),
        Sighting(*r[3], Sighting::animalTypes[2]),
        Sighting(*r[4], Sighting::animalTypes[3]),
        Sighting(*r[3], Sighting::animalTypes[2]),
        Sighting(*r[4], Sighting::animalTypes[3]),
        Sighting(*r[0], Sighting::animalTypes[3])
    };

    const int researcherSightings[NUM_RESEARCHERS] = {3, 2, 0, 2, 2};

    
 
    cout<<"Recording Sightings:"<<endl<<endl;
    
    for (int i = 0; i < numSightings; ++i){
        conservation.recordSighting(s[i]);
    }

    cout<<"Printing researchers and checking their sightings:"<<endl<<endl;

    for (int i = 0; i < NUM_RESEARCHERS; ++i){  
        r[i]->print();
        cout<<endl;
        if (r[i]->getNumSightings() != researcherSightings[i]){
            cout<<"Expected "<<researcherSightings[i]<<" sightings, found "<<r[i]->getNumSightings()<<", test failed, -1"<<endl;
            mark1 -= 1;
        }else{
            cout<<"Number of sightings correct"<<endl;
        }
    }

    if (mark1 < 0) mark1 = 0;

    cout<<"Researcher sightings test complete, marks: "<<mark1<<endl<<endl;
    marks += mark1;

    const string stationIds[NUM_STATIONS] = {"S1", "S2", "S3", "S4", "S5"};
    const int stationSightings[NUM_STATIONS] = {3, 2, 0, 0, 4};

    Station* sStation[NUM_STATIONS];
    cout<<"Reading Stations into an array"<<endl<<endl;
    for (int i = 0; i < NUM_STATIONS; ++i){  
        sStation[i] = conservation.getStation(stationIds[i]);
    }

    cout<<"Printing stations and checking their sightings:"<<endl<<endl;
    for (int i = 0; i < NUM_STATIONS; ++i){  
        sStation[i]->print();
        cout<<endl;
        if (sStation[i]->getNumSightings() != stationSightings[i]){
            cout<<"Expected "<<stationSightings[i]<<" sightings, found "<<sStation[i]->getNumSightings()<<", test failed, -1"<<endl;
            mark2 -= 1;
        }else{
            cout<<"Number of sightings correct"<<endl;
        }
    }

    if (mark2 < 0) mark2 = 0;
    cout<<"Station sightings test complete, marks: "<<mark2<<endl<<endl;
    marks += mark2;

    cout<<"Test complete, marks: "<<marks<<endl;
    return marks;;


}

int TestControl::testPrintStationSightings(){
    const int numStations = 3;
    Location tLocs[numStations]={Location(0,0), Location(5,5), Location(10,10)};
    Location cLocs[NUM_RESEARCHERS] = {Location(1,1), Location(4,6), Location(8,12), Location(19,21), Location(25,25)};
    Conservation conservation;
    conservation.resetIds();
    cout<<"4. Test print sightings at Station"<<endl<<endl;

    initStations(conservation, tLocs, numStations);
    initResearchers(conservation, cLocs, NUM_RESEARCHERS);

    cout<<"Recording sightings"<<endl;
    string animalSightings[4]= {Sighting::animalTypes[4], Sighting::animalTypes[0], Sighting::animalTypes[5], Sighting::animalTypes[2]};

    conservation.recordSighting("R1", animalSightings[0]);
    conservation.recordSighting("R2", animalSightings[1]);


    cout<<"Printing sightings in Station S1"<<endl;
    const List* sightings;
    // conservation.printStations();
    conservation.getSightingsHistory("S1", sightings);
    tester.initCapture();
    sightings->print();
    tester.endCapture();

    int error = 0;
    tester.find({0}, animalSightings, error);

    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        cout<<"Station print should print sightings"<<endl;
        return 0;
    }else{
        cout<<"All sightings found"<<endl<<endl;
    }

    cout<<"Printing sightings in Station S2"<<endl;
    conservation.getSightingsHistory("S2", sightings);
    tester.initCapture();
    sightings->print();
    tester.endCapture();

    tester.find({1}, animalSightings, error);

    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        return 0;
    }else{    
        cout<<"All sightings found"<<endl<<endl;
    }

    cout<<"Recording more sightings"<<endl<<endl;

    conservation.recordSighting("R1", animalSightings[2]);
    conservation.recordSighting("R3", animalSightings[3]);


    cout<<"Printing sightings in Station S1"<<endl;
    conservation.getSightingsHistory("S1", sightings);
    tester.initCapture();
    sightings->print();
    tester.endCapture();

    tester.find({0,2}, animalSightings, error);

    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        cout<<"Station print should print sightings"<<endl;
        return 0;
    }else{
        cout<<"All sightings found"<<endl<<endl;
    }

    tester.confirmAbsent({1,3}, animalSightings, error);

    if (error>0){
        cout<<error<<" incorrect sightings found, test failed"<<endl;
        return 0;
    }else{    
        cout<<"No incorrect sightings found"<<endl<<endl;
    }

    cout<<"Printing sightings in Station S3"<<endl;
    conservation.getSightingsHistory("S3", sightings);
    tester.initCapture();
    sightings->print();
    tester.endCapture();

    tester.find({3}, animalSightings, error);

    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        cout<<"Station print should print sightings"<<endl;
        return 0;
    }else{
        cout<<"All sightings found"<<endl<<endl;
    }

    tester.confirmAbsent({0,1,2}, animalSightings, error);

    if (error>0){
        cout<<error<<" incorrect sightings found, test failed"<<endl;
        return 0;
    }else{    
        cout<<"No incorrect sightings found"<<endl<<endl;
    }

    cout<<"Test complete, marks: 2"<<endl;
    return 2;
}
int TestControl::testPrintResearcherSightings(){
    Location tLocs[NUM_STATIONS]={Location(0,0), Location(5,5), Location(10,10), Location(15,15), Location(20,20)};
    Location cLocs[NUM_RESEARCHERS] = {Location(1,1), Location(4,6), Location(8,12), Location(19,21), Location(25,25)};
    Conservation conservation;
    conservation.resetIds();
    cout<<"5. Test print sightings from Researcher"<<endl<<endl;
    

    initStations(conservation, tLocs, NUM_STATIONS);
    initResearchers(conservation, cLocs, NUM_RESEARCHERS);

    cout<<"Recording sightings"<<endl;
    string animalSightings[4]= {Sighting::animalTypes[4], Sighting::animalTypes[0], Sighting::animalTypes[5], Sighting::animalTypes[2]};

    conservation.recordSighting("R1", animalSightings[0]);
    conservation.recordSighting("R2", animalSightings[1]);


    cout<<"Printing sightings from researcher R1"<<endl;
    const List* sightings;
    // conservation.printStations();
    conservation.getSightingsHistory("R1", sightings);
    tester.initCapture();
    sightings->print();
    tester.endCapture();

    int error = 0;
    tester.find({0}, animalSightings, error);

    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        cout<<"Station print should print sightings"<<endl;
        return 0;
    }else{
        cout<<"All sightings found"<<endl<<endl;
    }

    cout<<"Printing sightings from researcher R2"<<endl;
    conservation.getSightingsHistory("R2", sightings);
    tester.initCapture();
    sightings->print();
    tester.endCapture();

    tester.find({1}, animalSightings, error);

    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        return 0;
    }else{    
        cout<<"All sightings found"<<endl<<endl;
    }

    cout<<"Recording more sightings"<<endl<<endl;

    conservation.recordSighting("R1", animalSightings[2]);
    conservation.recordSighting("R3", animalSightings[3]);


    cout<<"Printing sightings from researcher R1"<<endl;
    conservation.getSightingsHistory("R1", sightings);
    tester.initCapture();
    sightings->print();
    tester.endCapture();

    tester.find({0,2}, animalSightings, error);

    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        cout<<"Station print should print sightings"<<endl;
        return 0;
    }else{
        cout<<"All sightings found"<<endl<<endl;
    }

    tester.confirmAbsent({1,3}, animalSightings, error);

    if (error>0){
        cout<<error<<" incorrect sightings found, test failed"<<endl;
        return 0;
    }else{    
        cout<<"No incorrect sightings found"<<endl<<endl;
    }

    cout<<"Printing sightings from researcher R3"<<endl;
    conservation.getSightingsHistory("R3", sightings);
    tester.initCapture();
    sightings->print();
    tester.endCapture();

    tester.find({3}, animalSightings, error);

    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        cout<<"Station print should print sightings"<<endl;
        return 0;
    }else{
        cout<<"All sightings found"<<endl<<endl;
    }

    tester.confirmAbsent({0,1,2}, animalSightings, error);

    if (error>0){
        cout<<error<<" incorrect sightings found, test failed"<<endl;
        return 0;
    }else{    
        cout<<"No incorrect sightings found"<<endl<<endl;
    }

    cout<<"Test complete, marks: 2"<<endl;
    return 2;

}

int TestControl::testPrintSightingsOfAnimal(){
    Location tLocs[NUM_STATIONS]={Location(0,0), Location(5,5), Location(10,10), Location(15,15), Location(20,20)};
    Location cLocs[NUM_RESEARCHERS] = {Location(1,1), Location(4,6), Location(8,12), Location(19,21), Location(25,25)};
    Conservation conservation;
    conservation.resetIds();
    cout<<"6. Test print sightings by animal"<<endl<<endl;
    

    initStations(conservation, tLocs, NUM_STATIONS);
    initResearchers(conservation, cLocs, NUM_RESEARCHERS);

    string researcherIds[10]= 
        {   "R1", 
            "R2", 
            "R1", 
            "R3",
            "R2",
            "R4",
            "R5",
            "R3",
            "R1",
            "R4"
        };

    Location researcherLocations[10] = {
        Location(1,1), //R1
        Location(4,6), //R2
        Location(1,1), //R1
        Location(8,12), //R3
        Location(4,6),  //R2
        Location(19,21), //R4
        Location(25,25), //R5
        Location(8,12), //R3
        Location(1,1), //R1
        Location(19,21), //R4
    };
    string animalSightings[10]= 
        {   Sighting::animalTypes[4], 
            Sighting::animalTypes[0], 
            Sighting::animalTypes[5], 
            Sighting::animalTypes[2],
            Sighting::animalTypes[5],
            Sighting::animalTypes[1],
            Sighting::animalTypes[3],
            Sighting::animalTypes[0],
            Sighting::animalTypes[6],
            Sighting::animalTypes[2]
        };
    
        string printedSightings[10];

    Researcher* r[NUM_RESEARCHERS];

    cout<<"Reading Researchers into an array"<<endl<<endl;

    
    r[0] = conservation.getResearcher("R1");
    r[1] = conservation.getResearcher("R2");
    r[2] = conservation.getResearcher("R3");
    r[3] = conservation.getResearcher("R4");
    r[4] = conservation.getResearcher("R5");
    
    
    cout<<"Printing some stuff for test purposes"<<endl<<endl;
    for (int i = 0; i < 10; ++i){
        Sighting temp(researcherIds[i], researcherLocations[i], animalSightings[i]);
        conservation.recordSighting(researcherIds[i], animalSightings[i]  );
        tester.initCapture(); 
        temp.print();
        tester.endCapture();
        cout<<endl;
        printedSightings[i] = tester.getOutput();
    }

    List sightingsOfAnimal;
    cout<<"Getting sightings of animal type "<<Sighting::animalTypes[0]<<endl;  
    conservation.getSightingsOf(Sighting::animalTypes[0], sightingsOfAnimal);
    cout<<"Printing sightings of animal type "<<Sighting::animalTypes[0]<<endl;

    
    tester.initCapture();
    sightingsOfAnimal.print();
    tester.endCapture();
    
    
    int error = 0;
    tester.find({1,7}, printedSightings, error);

    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        return 0;
    }else{
        cout<<"All sightings found"<<endl<<endl;
    }

    tester.find({0}, Sighting::animalTypes, error);

    if (error>0){
        cout<<error<<" sightings of "<<Sighting::animalTypes[0]<<" not found, test failed"<<endl;
        return 0;
    }else{
        cout<<"Animal type found"<<endl<<endl;
    }
    


    tester.confirmAbsent({0,2,3,4,5,6,8,9}, printedSightings, error);

    if (error>0){
        cout<<error<<" incorrect sightings found, test failed"<<endl;
        return 0;
    }else{    
        cout<<"No incorrect sightings found"<<endl<<endl;
    }
    
    cout<<"Getting sightings of animal type "<<Sighting::animalTypes[2]<<endl;  
    sightingsOfAnimal.clear();
    
    conservation.getSightingsOf(Sighting::animalTypes[2], sightingsOfAnimal);
    cout<<"Printing sightings of animal type "<<Sighting::animalTypes[2]<<endl;
    tester.initCapture();
    sightingsOfAnimal.print();
    tester.endCapture();


    error = 0;
    tester.find({3,9}, printedSightings, error);
    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        return 0;
    }else{
        cout<<"All sightings found"<<endl<<endl;    
    }

    tester.find({2}, Sighting::animalTypes, error);

    if (error>0){
        cout<<error<<" sightings of "<<Sighting::animalTypes[2]<<" not found, test failed"<<endl;
        return 0;
    }else{
        cout<<"Animal type found"<<endl<<endl;
    }

    tester.confirmAbsent({0,1,2,4,5,6,7,8}, printedSightings, error);


    if (error>0){
        cout<<error<<" incorrect sightings found, test failed"<<endl;
        return 0;
    }else{
        cout<<"No incorrect sightings found"<<endl<<endl;
    }
    
    cout<<"Getting sightings of animal type "<<Sighting::animalTypes[5]<<endl;  
    sightingsOfAnimal.clear();

    conservation.getSightingsOf(Sighting::animalTypes[5], sightingsOfAnimal);
    cout<<"Printing sightings of animal type "<<Sighting::animalTypes[5]<<endl;
    tester.initCapture();
    sightingsOfAnimal.print();
    tester.endCapture();
    error = 0;

    tester.find({2,4}, printedSightings, error);
    if (error>0){
        cout<<error<<" sightings not found, test failed"<<endl;
        return 0;
    }else{
        cout<<"All sightings found"<<endl<<endl;
    }

    tester.find({5}, Sighting::animalTypes, error);


    if (error>0){
        cout<<error<<" sightings of "<<Sighting::animalTypes[5]<<" not found, test failed"<<endl;
        return 0;
    }else{
        cout<<"Animal type found"<<endl<<endl;
    }

    tester.confirmAbsent({0,1,3,5,6,7,8,9}, printedSightings, error);
    if (error>0){
        cout<<error<<" incorrect sightings found, test failed"<<endl;
        return 0;
    }else{    
        cout<<"No incorrect sightings found"<<endl<<endl;
    }


    cout<<"No other sightings found."<<endl<<"Test passed, 2 marks"<<endl;

    return 2;
    

}

int TestControl::testMoveResearcher(){
    Location tLocs[NUM_STATIONS]={Location(0,0), Location(5,5), Location(10,10), Location(15,15), Location(20,20)};
    Location cLocs[NUM_RESEARCHERS] = {Location(1,1), Location(4,6), Location(8,12), Location(19,21), Location(25,25)};
    Conservation conservation;
    conservation.resetIds();
    cout<<"7. Test move researcher"<<endl<<endl;
    cout<<"This test will verify that after a researcher moves that its sightings are recorded by a different station. "<<endl<<endl;

    initStations(conservation, tLocs, NUM_STATIONS);
    initResearchers(conservation, cLocs, NUM_RESEARCHERS);

    cout<<"Recording a sighting from researcher R2 at location (4,6)"<<endl<<endl;
    conservation.recordSighting("R2", Sighting::animalTypes[0]);

    Researcher* c2 = conservation.getResearcher("R2");
    if (c2 == nullptr){
        cout<<"Could not find researcher R2, test failed"<<endl;
        return 0;
    }

    if (c2->getNumSightings() != 1){
        cout<<"Researcher R2 should have 1 sighting, found "<<c2->getNumSightings()<<", test failed"<<endl;
        return 0;
    }else{
        cout<<"Researcher R2 has 1 sighting as expected"<<endl<<endl;
    }

    Station* t2 = conservation.getStation("S2");

    if (t2 == nullptr){
        cout<<"Could not find station S2, test failed"<<endl;
        return 0;
    }

    if (t2->getNumSightings() != 1){
        cout<<"Station S2 should have 1 sighting, found "<<t2->getNumSightings()<<", test failed"<<endl;
        return 0;
    }else{
        cout<<"Station S2 has 1 sighting as expected"<<endl<<endl;
    }

    cout<<"Move R2 to (21,21)"<<endl<<endl;
    conservation.moveResearcher("R2", Location(21,21));

    cout<<"Recording 2 more sightings from researcher R2 at location (21,21)"<<endl;
    for (int i = 0; i < 2; ++i){
        conservation.recordSighting("R2", Sighting::animalTypes[0]);
    }

    if (c2->getNumSightings() != 3){
        cout<<"Researcher R2 should have 3 sightings, found "<<c2->getNumSightings()<<", test failed"<<endl;
        return 0;
    }else{
        cout<<"Researcher R2 has 3 sightings as expected"<<endl<<endl;
    }

    Station* t5 = conservation.getStation("S5");
    if (t5 == nullptr){
        cout<<"Could not find station S5, test failed"<<endl<<endl;
        return 0;
    }

    if (t5->getNumSightings() != 2){
        cout<<"Station S5 should have 2 sightings, found "<<t5->getNumSightings()<<", test failed"<<endl;
        return 0;  
    }else{
        cout<<"Station S5 has 2 sightings as expected"<<endl<<endl;
    }
    
    
    cout<<"Test passed, 2 marks"<<endl;


    return 2;

}