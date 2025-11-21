#ifndef RESEARCHER_H
#define RESEARCHER_H
#include <string>


#include "Entity.h"

class Researcher: public Entity{

    public:
        Researcher(const string& name, const Location& location);
        ~Researcher();
        static void resetId();
        void print() const;
        void setLocation(const Location& location);

        static int nextId;
        

    private:
        static const char code = 'R';
        string name;


};


#endif