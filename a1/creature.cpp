#include <iostream>
#include "creature.h"
using std::cout;



Creature::Creature(string n){
	name = n;
}

Creature::~Creature(){
}
/*
void Creature::move(Room* nextRoom){
	location = nextRoom;
	cout << "Creature has moved....";
	//concatenation operator: << or keep using + apparently
	//"2 leaves towards the east."
}*/

Room* Creature::getLocation(){
	return location;
}

string Creature::getName(){
	return name;
}


void Creature::setLocation(Room* l){
	location = l;
}

