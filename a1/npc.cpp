#include <iostream>
#include "creature.h"

class NPC : public Creature{
	
		public:
		
		NPC(string n) : Creature(n){}
		void reactToNewRoom(){
			cout<<endl;
			string cond = this->getLocation()->getCondition();
			if(cond == "clean"){
				this->getLocation()->changeCondition("dirty");
				cout<<this->getName()<<" dirties the room."<<endl;
			}
			cout<<endl;
		}
		
		void react(string actionPerformed){
			cout<<endl;
			if(actionPerformed == "clean"){
				cout<<this->getType()<<" "<<this->getName()<<" grumbles.";
				this->getLocation()->getPC()->lowerRespect();
				cout<<" Respect is now "<<this->getLocation()->getPC()->getRespect()<<endl;
			} else if(actionPerformed == "dirty"){
				cout<<this->getType()<<" "<<this->getName()<<" smiles.";
				this->getLocation()->getPC()->addRespect();
				cout<<" Respect is now "<<this->getLocation()->getPC()->getRespect()<<endl;

			}
			if(this->getLocation()->getCondition() == "clean"){
				this->move();
			}
			cout<<endl;
		
		}
		void reactDirected(string actionPerformed){
			cout<<endl;
			if(actionPerformed == "clean"){
				cout<<this->getName()<<" grumbles your face alot.";
				this->getLocation()->getPC()->addRespect();
				this->getLocation()->getPC()->addRespect();
			} else if(actionPerformed == "dirty"){
				cout<<this->getName()<<" smiles alot."<<endl;
				this->getLocation()->getPC()->lowerRespect();
				this->getLocation()->getPC()->lowerRespect();
			}
			cout<<endl;
		}
		
		string getType(){
			return "npc";
		}
		
		void clean(){
			this->reactDirected("clean");
			this->getLocation()->changeCondition("clean");
		}
		
		void dirty(){
			this->reactDirected("dirty");
			this->getLocation()->changeCondition("dirty");
		}
		
		void moveDirected(string direction){
			Room* previousRoom = this->getLocation();
			this->getLocation()->getAdjacent(direction)->addCreature(this);
			previousRoom->removeCreature(this);
			this->reactToNewRoom();
		}
		
		void move(){
			bool found = false;
			for(int i = 0; i<4; i++){
				if(this->getLocation()->getAdjacent()[i] != NULL){
					Room* previousRoom = this->getLocation();
					if(this->getLocation()->getAdjacent()[i]->addCreature(this)){
					previousRoom->removeCreature(this);
					this->reactToNewRoom();
					found = true;
					}
				}
			}
			if(found == false){
				cout<<this->getType()<<" "<<this->getName()<<" was unable to move."<<endl;
				this->react("dirty");
			}
			
		}
};