#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <string>
#include "List.h"
#include <random>
#include <unordered_set>
#include <sstream>
#include "Station.h"
#include "Researcher.h"
#include "View.h"
#include "Conservation.h"

using namespace std;

class Control {
		
	public:
		void launch();
	
	private:
		void init();
		void addStation();
		void addResearcher();
		
		void moveResearcher();
		void printStations();
		void printResearchers();
		// maybe printall?

		void recordSighting();

		void printStationSightings();
		void printResearcherSightings();
		void printSightingsOf();


		void addR(string& id);
		void addS(string& id);
	
		

		View view;
		Conservation conservation;

	
};
#endif