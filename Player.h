//CS 246 A6 - hx3zhang/z289wang 
//Implemented in Player.cc

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "Card.h" 
#include <vector>
#include <string>
#include "PRNG.h"

using namespace std;

class Player {
  
  public:
	Player();
	Player(string name); //Constructor with name
	virtual ~Player();
	Card* playCard(int highRank, int suit); //Funtion to pick a card
	void addPoints(int val); //Add points to a player
	int getScore () const; //Get player's score
	string getName () const; //Get player's name
	void draw(Card* c); //Take a card from the deck and add to player's hand
	string printHand(); //Returns as a string the contetns of a player's hand
      
  protected:
	vector<Card*> hand; //The player's hand
	virtual int lead() = 0; //When a player is the first in a trick
	virtual int throwOff() = 0; //When a player has no cards of trump suit
    virtual int followSuit(int highRank, int suit) = 0; //When a player has cards of a trump suit
	int points; //Total points of player
	string name; //Name of player
};


#endif
