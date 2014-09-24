/*
 * SmartPlayer.h
 *
 *  Created on: Dec 1, 2012
 *      Author: hx3zhang
 */

#ifndef SMARTPLAYER_H_
#define SMARTPLAYER_H_

#include <string>
#include "Player.h"

using namespace std;

class SmartPlayer : public Player {
	public:
	//constructor
	SmartPlayer(string name);

	protected:
	int lead();
	int throwOff();
	int followSuit(int highRank, int suit);
};

#endif /* SMARTPLAYER_H_ */
