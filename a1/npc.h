#ifndef NPC_H
#define NPC_H
#include <iostream>
#include "creature.h"

class NPC : public Creature{
	
		public:
		
		NPC(string n) : Creature(n){}
		void reactToNewRoom(){
			string cond = this->getLocation()->getCondition();
			if(cond == "clean"){
				this->getLocation()->changeCondition("dirty", this, true);
			}
			cout<<endl;
		}
		
		void react(string actionPerformed, bool couldntMove){
			if(actionPerformed == "clean"){
				cout<<this->getType()<<" "<<this->getName()<<" grumbles.";
				this->getLocation()->getPC()->lowerRespect();
				cout<<" Respect is now "<<this->getLocation()->getPC()->getRespect()<<endl;
			} else if(actionPerformed == "dirty"){
				cout<<this->getType()<<" "<<this->getName()<<" smiles.";
				this->getLocation()->getPC()->addRespect();
				cout<<" Respect is now "<<this->getLocation()->getPC()->getRespect()<<endl;

			}
			if(this->getLocation()->getCondition() == "clean" && couldntMove == false){
				this->move();
			}
			cout<<endl;
		
		}
		bool reactDirected(string actionPerformed, bool onArrival){
			if(actionPerformed == "clean"){
				cout<<this->getName()<<" grumbles your face alot.";
				this->getLocation()->getPC()->lowerRespect();
				this->getLocation()->getPC()->lowerRespect();
				this->getLocation()->getPC()->lowerRespect();
				cout<<" Respect is now "<<this->getLocation()->getPC()->getRespect()<<endl;
			} else if(actionPerformed == "dirty" ){
				cout<<this->getName()<<" smiles alot.";
				this->getLocation()->getPC()->addRespect();
				this->getLocation()->getPC()->addRespect();
				this->getLocation()->getPC()->addRespect();
				cout<<" Respect is now "<<this->getLocation()->getPC()->getRespect()<<endl;
			}
			if(this->getLocation()->getCondition()=="clean" && onArrival == false){
				this->move();
				return true;
			}
			cout<<endl;
			return false;
		}
		
		string getType(){
			return "npc";
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
		
		void moveDirected(string direction){
			Room* previousRoom = this->getLocation();
			this->getLocation()->getAdjacent(direction)->addCreature(this);
			previousRoom->removeCreature(this);
			this->reactToNewRoom();
		}
		
		void move(){
			bool found = false;
			for(int i = 0; i<4; i++){
				if(this->getLocation()->getAdjacent()[i] != NULL && found == false){
					Room* previousRoom = this->getLocation();
					if(this->getLocation()->getAdjacent()[i]->addCreature(this)){
					previousRoom->removeCreature(this);
					found = true;
					string direction;
					this->reactToNewRoom();
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
				this->react("dirty", true);
			}
			
		}
};
#endif