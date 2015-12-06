#include <iostream>
#include "creature.h"
using std::cout;

class PC : public Creature{
	public:
	
		PC(string n) : Creature(n){respect = 40;};
	
		int getRespect(){
			return respect;
		}
		
		void look(){
			cout<<"\n"<<"Room "<<this->getLocation()->getName() <<", "
			<< this->getLocation()->getCondition() <<", neighbors ";
			for(int i=0; i<4; i++){
				if(this->getLocation()->getAdjacent()[i] != NULL){
					cout<<this->getLocation()->getAdjacent()[i]->getName();
					if(i == 0){
						cout<<" to the north, ";
					} else if(i == 1){
						cout<<" to the south, ";
					} else if(i == 2){
						cout<<" to the east, ";
					} else if(i == 3){
						cout<<" to the west, ";
					}
				}
			}
			cout<<"contains:"<<endl;
			for(int i=0; i<4; i++){
				if(this->getLocation()->getCreatures()[i] != NULL){
					cout<<this->getLocation()->getCreatures()[i]->getType() << " ";
					cout<<this->getLocation()->getCreatures()[i]->getName()<<endl;
				}
			}
			cout<<endl;
		}
		
		void addRespect(){
			respect = respect + 1;
		}
		void lowerRespect(){
			respect = respect -1;
		}
		void clean(){
			this->getLocation()->changeCondition("clean");
		}
		void dirty(){
			this->getLocation()->changeCondition("dirty");
		}
		
		string getType(){
			return "PC";
		}
		
		void moveDirected(string direction){
			Room* previousRoom = this->getLocation();
			this->getLocation()->getAdjacent(direction)->addCreature(this);
			previousRoom->removeCreature(this);
		}
	
	private:
		int respect;
	
};
