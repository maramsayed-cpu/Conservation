#ifndef STATION_H
#define STATION_H
#include <string>


#include "Entity.h"


class Station: public Entity{

    public:
        Station(const Location& location);
        ~Station();
        static void resetId();

        void print() const;
        static int nextId;
        


    private:
        static const char code = 'S';


};


#endif

