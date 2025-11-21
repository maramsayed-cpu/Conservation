#ifndef ResearcherLIST_H
#define RESEARCHERLIST_H

#define MAX_ARR 64

#include "Researcher.h"

class ResearcherList
{
  class Node {


        public:
            Researcher* data;
            Node*    next;
          };

  public:
      ResearcherList();
      ~ResearcherList();

      bool isEmpty() const;
      Researcher* removeFirst();
      void add(const string& name, const Location& location);
      void print() const;
      void clear();
      Researcher* get(int index) const;



  private:
      Node* head;
      Node* tail;
      int tracker;

   
};

#endif

