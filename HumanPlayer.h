//CS 246 A6 - hx3zhang/z289wang 
//Implemented in HumanPlayer.cc

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include <string>
#include "Player.h"

using namespace std;

class HumanPlayer : public Player{
	public:
	HumanPlayer(string Name);
	
	protected:
	//Also see player.h
	int lead();
	int throwOff();
	int followSuit(int highRank, int suit);
	int interact(int suit); //Handles the player input/output
};


#endif /* HUMANPLAYER_H_ */
