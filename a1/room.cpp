
#include "room.h"
#include "creature.h"
using namespace std;
class Creature;
Room::Room(string n){
	name = n;
	creatures = new Creature*[10];
	adjacentRoomsP = new Room*[4];
	cout<<"creating room " << this->getName() << endl;
	
}

Room::~Room(){
	delete[] adjacentRoomsP;
	delete[] creatures;
}

Room* Room::getAdjacent(string direction){
	if(direction == "north"){
		return adjacentRoomsP[0];
	} else if(direction == "south"){
		return adjacentRoomsP[1];
	} else if(direction == "east"){
		return adjacentRoomsP[2];
	} else if(direction == "west"){
		return adjacentRoomsP[3];
	}
}

void Room::addAdjacent(Room* a, int direction){
	bool stop = false;
	for(int i = 0; i < 4; i++){
		if(direction == 0){
			if(adjacentRoomsP[0] == NULL && stop == false){
				adjacentRoomsP[0] = a;
				cout<<"adding pointer " << a->getName() << " as neighbor in direction north."<<endl;
				stop = true;
			}
		}else if(direction == 1){
			if(adjacentRoomsP[1] == NULL && stop == false){
				adjacentRoomsP[1] = a;
				cout<<"adding pointer to room " << a->getName() << " as neighbor in direction south."<<endl;
				stop = true;
			}
		}else if(direction == 2){
			if(adjacentRoomsP[2] == NULL && stop == false){
				adjacentRoomsP[2] = a;
				cout<<"adding pointer to room " << a->getName() << " as neighbor in direction east."<<endl;
				stop = true;
			}
		} else if(direction == 3){
			if(adjacentRoomsP[3] == NULL && stop == false){
				adjacentRoomsP[3] = a;
				cout<<"adding pointer to room " << a->getName() << " as neighbor in direction west."<<endl;
				stop = true;
			}
		}
		
	}
}

void Room::setCondition(string cond){
	condition = cond;
	cout << "setting room " << this->getName() << "'s condition to " << cond << endl;
}

void Room::changeCondition(string actionPerformed, Creature* performer, bool onArrival){
	if(condition == "clean" && actionPerformed == "dirty"){
		condition = "half-dirty";
		if(onArrival==false){
			this->notifyCreatures(actionPerformed, performer);
		}
	} else if (condition == "half-dirty" && actionPerformed == "dirty"){
		condition = "dirty";
		if(onArrival==false){
			this->notifyCreatures(actionPerformed, performer);
		}
	} else if (condition == "half-dirty" && actionPerformed == "clean"){
		condition = "clean";
		if(onArrival==false){
			this->notifyCreatures(actionPerformed, performer);
		}
	} else if (condition ==  "dirty" && actionPerformed == "clean"){
		condition = "half-dirty";
		if(onArrival==false){
			this->notifyCreatures(actionPerformed, performer);
		}
	}
}

void Room::notifyCreatures(string actionPerformed, Creature* performer){
	for(int i = 0; i<10; i++){
		if(this->getCreatures()[i] != NULL && this->getCreatures()[i] != performer
					&& this->getCreatures()[i]->getType() != "PC"){
			this->getCreatures()[i]->react(actionPerformed, false);
		}
	}
}

string Room::getName(){
	return name;
}


string Room::getCondition(){
	return condition;
}

bool Room::addCreature(Creature* c){
	for(int i = 0; i < 10; i++){
		if(this->getCreatures()[i] == NULL){
			creatures[i] = c;
			c->setLocation(this);
			return true;
		}
	} 
	return false;
}

void Room::removeCreature(Creature* c){
	for(int i = 0; i< 10; i++){
		if(this->getCreatures()[i]==c){
			creatures[i]=NULL;
		}
	}
}

Creature* Room::getPC(){
	for(int i = 0; i<10; i++){
		if(this->getCreatures()[i]!=NULL){
			if(this->getCreatures()[i]->getType()=="PC"){
			return this->getCreatures()[i];
			}
		}
		
	}
}


