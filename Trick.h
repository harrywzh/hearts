//CS 246 A6 - hx3zhang/z289wang 
//Implemented in Trick.cc

#ifndef _TRICK_H_
#define _TRICK_H_

#include<iostream>
#include "Card.h"
using namespace std;

class Trick {
	
    public:
	Trick (); //Constructior
	int addCard(Card* c, int pid); //Adds a card to the trick
	int getValue () const; //Get hearts value of trick
	int getWinner () const; //Get current winner of trick
	string getCards(); //Get a string showing the cards in the trick
	
	private:
	int winner, value, turn; //Data variables
	Card* highCard; //The current highest cad in the trick (of the trump suit)
	string contents; //Stores a string of the cards in the deck
};

#endif
