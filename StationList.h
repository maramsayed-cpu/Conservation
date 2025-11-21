#ifndef STATIONLIST_H
#define STATIONLIST_H

#define MAX_ARR 64

#include "Station.h"

class StationList
{
  class Node {


        public:
            Station* data;
            Node*    next;
          };

  public:
      StationList();
      ~StationList();

      bool isEmpty() const;
      Station* removeFirst();
      void add(const Location& location);
      void print() const;
      void clear();
      Station* get(int index) const;



  private:
      Node* head;
      Node* tail;
      int tracker;

   
};

#endif

