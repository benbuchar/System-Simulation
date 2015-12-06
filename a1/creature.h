#ifndef CREATURE_H
#define CREATURE_H
#include "room.h"
#include <iostream>
#include <sstream>
class Room;
using namespace std;

class Creature {
	public:
	    virtual void reactToNewRoom(){};
		virtual void clean(bool onArrival){};
		virtual void clean(){};
		virtual void dirty(bool onArrival){};
		virtual void dirty(){};
		virtual void moveDirected(string direction){};
		virtual void move(){};
		virtual void react(string actionPerformed, bool couldntMove){};
		virtual void addRespect(){};
		virtual void lowerRespect(){};
		void setLocation(Room* l);
		virtual string getType(){};
		virtual void look(){};
		virtual int getRespect(){};
		
		Room* getLocation();
		string getName();
		Creature(string n);
		~Creature();
		
	private:
		string name;
		Room* location;
};

#endif