#include <iostream>
#include "creature.h"
using std::cout;

class Animal : public Creature{
	public:
		Animal(string n) : Creature(n){};
		void reactToNewRoom(){
			string cond = this->getLocation()->getCondition();
			if(cond == "dirty"){
				cout<<this->getName()<<" cleans room "<<this->getLocation()->getName()<<endl;
				this->getLocation()->changeCondition("clean");
			}
		}
		
		string getType(){
			return "animal";
		}
		
		void react(string actionPerformed){
			cout<<endl;
			if(actionPerformed == "clean"){
				cout<<this->getType()<<" "<<this->getName()<<" licks the PC's face.";
				this->getLocation()->getPC()->addRespect();
				cout<<" Respect is now "<<this->getLocation()->getPC()->getRespect()<<endl;
			} else if(actionPerformed == "dirty"){
				cout<<this->getType()<<" "<<this->getName()<<" growls.";
				this->getLocation()->getPC()->lowerRespect();
				cout<<" Respect is now "<<this->getLocation()->getPC()->getRespect()<<endl;
			}
			if(this->getLocation()->getCondition() == "dirty"){
				this->move();
			}
			cout<<endl;
		}
		
		void reactDirected(string actionPerformed){
			cout<<endl;
			if(actionPerformed == "clean"){
				cout<<this->getType()<<" "<<this->getName()<<" licks your face alot."<<endl;
				this->getLocation()->getPC()->addRespect();
				this->getLocation()->getPC()->addRespect();
			} else if(actionPerformed == "dirty"){
				cout<<this->getType()<<" "<<this->getName()<<" growls alot."<<endl;
				this->getLocation()->getPC()->lowerRespect();
				this->getLocation()->getPC()->lowerRespect();
			}
			cout<<endl;
		}
		
		
		void clean(){
			this->reactDirected("clean");
			this->getLocation()->changeCondition("clean");
		}
		
		void dirty(){
			this->reactDirected("dirty");
			this->getLocation()->changeCondition("dirty");
		}
		
		
		void move(){
			bool found = false;
			for(int i = 0; i<4; i++){
				if (found){
					break;
				}
				if(this->getLocation()->getAdjacent()[i] != NULL){
					Room* previousRoom = this->getLocation();
					bool success = this->getLocation()->getAdjacent()[i]->addCreature(this);
					if(success){
					previousRoom->removeCreature(this);
					this->reactToNewRoom();
					found = true;
					}
				}
			}
			if(found == false){
				cout<<this->getType()<<" "<<this->getName()<<" was unable to move."<<endl;
				this->react("clean");
			}
			
		}
		
		void moveDirected(string direction){
			Room* previousRoom = this->getLocation();
			this->getLocation()->getAdjacent(direction)->addCreature(this);
			previousRoom->removeCreature(this);
			this->reactToNewRoom();
		}
		
};