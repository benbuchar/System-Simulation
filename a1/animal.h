#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>
#include "creature.h"
using std::cout;

class Animal : public Creature{
	public:
		Animal(string n) : Creature(n){};
		void reactToNewRoom(){
			string cond = this->getLocation()->getCondition();
			if(cond == "dirty"){
				this->getLocation()->changeCondition("clean", this, true);
			}
		}
		
		string getType(){
			return "animal";
		}
		
		void react(string actionPerformed, bool couldntMove){
			cout<<"entering react method"<<endl;
			if(actionPerformed == "clean"){
				cout<<"actionPerformed was clean"<<endl;
				cout<<this->getType()<<" "<<this->getName()<<" licks the PC's face.";
				this->getLocation()->getPC()->addRespect();
				cout<<" Respect is now "<<this->getLocation()->getPC()->getRespect()<<endl;
			} else if(actionPerformed == "dirty"){
				cout<<this->getType()<<" "<<this->getName()<<" growls.";
				this->getLocation()->getPC()->lowerRespect();
				cout<<" Respect is now "<<this->getLocation()->getPC()->getRespect()<<endl;
			}
			if(this->getLocation()->getCondition() == "dirty" && couldntMove==false){
				this->move();
			}
			cout<<endl;
		}
		
		void reactDirected(string actionPerformed, bool onArrival){
			if(actionPerformed == "clean"){
				cout<<this->getType()<<" "<<this->getName()<<" licks your face alot.";
				this->getLocation()->getPC()->addRespect();
				this->getLocation()->getPC()->addRespect();
				this->getLocation()->getPC()->addRespect();
				cout<<" Respect is now: "<<this->getLocation()->getPC()->getRespect()<<endl;
			} else if(actionPerformed == "dirty"){
				cout<<this->getType()<<" "<<this->getName()<<" growls alot.";
				this->getLocation()->getPC()->lowerRespect();
				this->getLocation()->getPC()->lowerRespect();
				this->getLocation()->getPC()->lowerRespect();
				cout<<" Respect is now: "<<this->getLocation()->getPC()->getRespect()<<endl;

			}
			if(this->getLocation()->getCondition() == "dirty" && onArrival == false){
				this->move();
			}
			cout<<endl;
		}
		
		
		void clean(bool onArrival){
			if(this->getLocation()->getCondition()!="clean"){
				this->getLocation()->changeCondition("clean", this, onArrival);
				this->reactDirected("clean", onArrival);
			}	
		}
		
		void dirty(bool onArrival){
			if(this->getLocation()->getCondition()!="dirty"){
				this->getLocation()->changeCondition("dirty", this, onArrival);
				this->reactDirected("dirty", onArrival);
			}
						
		}
		
		
		void move(){
			bool found = false;
			for(int i = 0; i<4; i++){
				if(this->getLocation()->getAdjacent()[i] != NULL && found == false){
					Room* previousRoom = this->getLocation();
					bool success = this->getLocation()->getAdjacent()[i]->addCreature(this);
					if(success){
						previousRoom->removeCreature(this);
						this->reactToNewRoom();
						found = true;
						string direction;
						if(i == 0){
							direction = "north";
						} else if(i == 1){
							direction = "south";
						} else if(i == 2){
							direction = "east";
						} else if(i == 3){
							direction ="west";
						}
						cout<<this->getType()<<" "<<this->getName()<<" leaves towards the "<<direction<<endl;
					}
				}
			}
			if(found == false){
				cout<<this->getType()<<" "<<this->getName()<<" was unable to move."<<endl;
				this->react("clean", true);
			}
			
		}
		
		void moveDirected(string direction){
			Room* previousRoom = this->getLocation();
			this->getLocation()->getAdjacent(direction)->addCreature(this);
			previousRoom->removeCreature(this);
			this->reactToNewRoom();
		}
		
};
#endif