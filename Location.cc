
#include "Location.h"

Location::Location(int x, int y){
    this->x = x;
    this->y = y;
}

void Location::setLocation(int x, int y){
    this->x = x;
    this->y = y;
}

int Location::getDistance(const Location& l) const{
    return abs(l.x-x)+abs(l.y-y);
}


void Location::print() const{  
    cout<<"Latitude: "<<x<<", Longitude: "<<y<<endl;
}



