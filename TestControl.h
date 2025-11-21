// I didn't write this code 

#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <sstream>
#include "Conservation.h"
#include "View.h"
#include "Tester.h"

using namespace std;

class TestControl {
		
	public:
		void launch();
	
	private:
		void initStations(Conservation& conservation, Location* locations, int numStations);
		void initResearchers(Conservation& conservation, Location* locations, int numResearchers);
		int testAddStations();
		int testAddResearchers();
		int testRecordSighting();
		int testPrintStationSightings();
		int testPrintResearcherSightings();
		int testPrintSightingsOfAnimal();
		int testMoveResearcher();
		

		View view;
		Tester tester;
	

		
	
};

#endif
