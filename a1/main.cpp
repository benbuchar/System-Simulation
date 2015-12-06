#include <iostream>
#include <sstream>
#include <string>
#include "room.cpp"
#include "creature.cpp"
#include "animal.h"
#include "npc.h"
#include "pc.h"



int main(){
	
	cout<<"Welcome to the game."<<endl;
	
	int numberOfRooms;
	cin>>numberOfRooms;
	
	Room* rooms[numberOfRooms];
	
	for(int i = 0; i<numberOfRooms; i++){
		string name;
		stringstream ss;
		ss<<i;
		name = ss.str();
		rooms[i] = new Room(name);
		//Room* r = new Room(name);
		//rooms[i] = r;
	}
	
	for(int i = 0; i<numberOfRooms; i++){
		string s;
		getline(cin, s);
		string line2;
		
		istringstream iss(s);
		
		string subs[5];
		if(i == 0){
			getline(cin, line2);
			istringstream iss2(line2);
			int j = 0;
		do{
			string sub;
			iss2 >> sub;
			if(sub != ""){
				subs[j] = sub;
				j++;
			}
			
		} while(iss2);
		
		if(subs[0]=="0"){
				rooms[i]->setCondition("clean");
			} else if(subs[0]=="1"){
				rooms[i]->setCondition("half-dirty");
			} else if(subs[0]=="2"){
				rooms[i]->setCondition("dirty");
			}
		
		for(int k = 1; k<5; k++){
			if(subs[k] != "-1"){
				for(int meow = 0; meow<numberOfRooms; meow++){
					if(rooms[meow]->getName() == subs[k]){
						rooms[i]->addAdjacent(rooms[meow], k-1);
					}	
				}
			}
		}
			
		} else {
		
			int j = 0;
			do{
				string sub;
				iss >> sub;
				if(sub != ""){
					subs[j] = sub;
					j++;
				}
			
			} while(iss);
		
			if(subs[0]=="0"){
				rooms[i]->setCondition("clean");
			} else if(subs[0]=="1"){
				rooms[i]->setCondition("half-dirty");
			} else if(subs[0]=="2"){
				rooms[i]->setCondition("dirty");
			}
			
		
			for(int k = 1; k<5; k++){
				if(subs[k] != "-1"){
					for(int meow = 0; meow<numberOfRooms; meow++){
						if(rooms[meow]->getName() == subs[k]){
							rooms[i]->addAdjacent(rooms[meow], k-1);
						}	
					}
				}
			}
		}
		
	}
	int numberOfCreatures;
	cin>>numberOfCreatures;
	Creature* creatures[numberOfCreatures];
	Creature* pc;
	for(int i = -1; i<numberOfCreatures; i++){
		string line;
		getline(cin, line);
		istringstream iss(line);
		string subs[2];
			
		int d = 0;
		do{
			string sub;
			iss>>sub;
			subs[d] = sub;
			d++;
		} while(iss);
		string name;
		stringstream ss;
		ss<<i;
		name = ss.str();
		//Creature* c;
		if(subs[0]=="0"){
			creatures[i] = new PC(name);
			pc = creatures[i];
			//creatures[i] = c;
		} else if(subs[0]=="1"){
			creatures[i] = new Animal(name);
			//creatures[i] = c;
		} else if(subs[0]=="2"){
			creatures[i] = new NPC(name);
			//creatures[i] = c;
		}
		
		for(int q = 0; q<numberOfRooms; q++){
			if(rooms[q]->getName() == subs[1]){
				rooms[q]->addCreature(creatures[i]);
			}
		}
		
		
		
			
	}
	
	
	string command = "";
	do{ 
		getline(cin, command);
		cout<<endl;
		if(command.find(":")==string::npos){
			if(command == "clean"){
				pc->clean();
			} else if(command =="dirty"){
				pc->dirty();
			} else if(command =="look"){
				pc->look();
			} else if(command == "east"){
				pc->moveDirected("east");
			} else if(command == "west"){
				pc->moveDirected("west");
			} else if(command =="north"){
				pc->moveDirected("north");
			} else if(command =="south"){
				pc->moveDirected("south");
			}
		} else{
			string name = command.substr(0, command.find(":"));
			string action = command.substr(command.find(":")+1);
			
			if(action == "clean"){
				for(int h = 0; h<numberOfCreatures; h++){
					if(pc->getLocation()->getCreatures()[h]!=NULL){
						if(pc->getLocation()->getCreatures()[h]->getName() == name){
							pc->getLocation()->getCreatures()[h]->clean(false);
						}
					}
				}
			} else if(action == "dirty"){
				for(int h = 0; h<numberOfCreatures; h++){
					if(pc->getLocation()->getCreatures()[h]!=NULL){
						if(pc->getLocation()->getCreatures()[h]->getName() == name){
							pc->getLocation()->getCreatures()[h]->dirty(false);
						}
					}
				}
			} else if(action == "north" || action == "south" || action =="east"
						|| action == "west"){
				for(int h = 0; h<numberOfCreatures; h++){
					if(pc->getLocation()->getCreatures()[h]!=NULL){
						if(pc->getLocation()->getCreatures()[h]->getName() == name){
							pc->getLocation()->getCreatures()[h]->moveDirected(action);
						}
					}
				}
			}
		}
	}	while(command != "exit" && pc->getRespect()!=0 && pc->getRespect()!=80);
	
	if(pc->getRespect()==0){
		cout<<"You lost the game. Boo."<<endl;
	} else if(pc->getRespect()==100){
		cout<<"You won the game! Wow!"<<endl;
	}
	//delete pc;
	cout<<"Goodbye."<<endl;
	
	
	for(int i = 0; i<numberOfCreatures; i++){
		if(creatures[i]!=NULL){
			delete creatures[i];
		}
		
	}
	for(int i = 0; i<numberOfRooms; i++){
		if(rooms[i]!=NULL){
			delete rooms[i];
		}
		
	}
	//delete pc;
}