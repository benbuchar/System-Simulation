#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <sstream>

#include "creature.h"
using namespace std;

class Room {
	public:
		int clean();
		int dirty();
		Room(string n);
		~Room();
		void addAdjacent(Room* a, int direction);
		Room* getAdjacent(string direction);
		void setCondition(string cond);
		void changeCondition(string cond, Creature* performer, bool onArrival);
		void notifyCreatures(string actionPerformed, Creature* performer);
		Creature** getCreatures(){return creatures;}
		Room** getAdjacent(){return adjacentRoomsP;}
		Creature* getPC();
		string getName();
		string getCondition();
		bool addCreature(Creature* c);
		void removeCreature(Creature* c);
	
	private:
		string name;
		string condition;
		Creature** creatures;
		Room** adjacentRoomsP;
};

#endif