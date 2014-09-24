//CS 246 A6 - hx3zhang/z289wang 
//Implemented in RandomPlayer.cc

#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

#include <string>
#include "Player.h"

using namespace std;

class RandomPlayer : public Player {
public:
	//constructor
	RandomPlayer(string name);
	RandomPlayer(string name,int seed); //Randomplayers require a seed for its PRNG

protected:
	PRNG prng; //Each Randomplayer has its own instance of PRNG
	int lead();
	int throwOff();
	int followSuit(int highRank, int suit);
};


#endif /* RANDOMPLAYER_H_ */
