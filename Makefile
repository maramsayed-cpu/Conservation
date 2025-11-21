objects = test.o Researcher.o Entity.o Station.o Location.o Sighting.o List.o Tester.o ResearcherList.o StationList.o Conservation.o Control.o TestControl.o View.o 

all: a3
	
a3: $(objects)
	g++ -o a3 $(objects)


test.o: test.cc TestControl.h
	g++ -c test.cc

TestControl.o:	TestControl.h TestControl.cc Conservation.h View.h Tester.h
	g++ -c TestControl.cc

Control.o:	Control.h Control.cc Station.h Researcher.h View.h Conservation.h
	g++ -c Control.cc

View.o:	View.h View.cc List.h
	g++ -c View.cc

Conservation.o: Conservation.h Conservation.cc ResearcherList.h StationList.h Sighting.h Location.h
	g++ -c Conservation.cc

StationList.o: StationList.h StationList.cc Station.h
	g++ -c StationList.cc

ResearcherList.o: ResearcherList.h ResearcherList.cc Researcher.h
	g++ -c ResearcherList.cc

Researcher.o: Researcher.h Researcher.cc Entity.h
	g++ -c Researcher.cc

Entity.o: Entity.h Entity.cc Location.h List.h 
	g++ -c Entity.cc

List.o:	List.h List.cc Sighting.h
	g++ -c List.cc

Sighting.o:	Sighting.h Sighting.cc Location.h Researcher.h
	g++ -c Sighting.cc

Station.o:	Station.h Station.cc Location.h Entity.h
	g++ -c Station.cc


Location.o:	Location.h Location.cc
	g++ -c Location.cc

Tester.o:	Tester.h Tester.cc
	g++ -c Tester.cc

clean:
	rm -f test *.o
