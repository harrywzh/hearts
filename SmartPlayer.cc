/*------------------------
  CS246 - Assignment 6
  "SmartPlayer.cc" 
  hx3zhang | 20437677
  z289wang | 20436476
  Due Date 2012/12/03 
------------------------*/

#include <string>
#include "Player.h"
#include "SmartPlayer.h"

using namespace std;

//constructor
SmartPlayer::SmartPlayer(string name) : Player::Player(name){
	this->name = 's' + this->name;
}
//add prefix

//lead, throwOff, and followSuit
//These functions are called from Player::playCard. They return an integer value (not a Card or Card*), representing the relative location of the 
//card to be played in the player's hand. playCard will then retrieve the card and pass it back to the main program.

//Unsigned int in for loops to avoid compiler warnings

//lead - picks the lowest card according to specified ordering and plays it
int SmartPlayer::lead(){
	int lowest = 0;
	for (unsigned int i = 0; i < hand.size(); i++){
		if (*hand[i] < *hand[lowest]) lowest = i;	
	}
	return lowest;	
}

//throwOff - Throws (in priority) QS or higest Rank heart or highest Rank card
int SmartPlayer::throwOff(){
	int highVal = 0;
	bool hearts = false;
	for (unsigned int i = 0; i < hand.size(); i++){
		if (hand[i]->getSuit() == Card::Hearts){
		//If first hearts, reset highVal to the hearts card, if not first hearts, check which is bigger
			if (hearts){
				if (*hand[highVal] < *hand[i]) highVal = i;
			} else {
				hearts = true;
				highVal = i;
			}
		//If QS, immediately return it
		} else if (*hand[i] == hand[i]->QueenOfSpades){
			return i; 
		} else {
		//If no hearts have been played, store the card with highest Rank
			if (!hearts && *hand[highVal] < *hand[i]) highVal = i;
		}
	}
	return highVal;
}

//followSuit - plays based on the specified algorithm described in the assignment
//This function can also return -1, meaning a card of the suit has not been found
int SmartPlayer::followSuit(int highRank, int suit){
	int ret = 0; //Return Value
	bool hasLower = false;
	bool hasSuit = false;

	for (unsigned int i = 0; i < hand.size(); i++){
		if (hand[i]->getSuit() == suit){
			//first time there is the correct suit, set initial value as current value
			if (!hasSuit){
				hasSuit = true;
				ret = i;
			} 
			//If there is already a card lower than highcard, pick the highest card
			if (hasLower){
				if(hand[i]->getRank() < highRank && hand[ret]->getRank() < hand[i]->getRank()) ret = i;
			} else if(hand[i]->getRank() < highRank){
				ret = i;
				hasLower = true;
			//Otherwise pick the lowest card
			} else {
				if(hand[i]->getRank() < hand[ret]->getRank()) ret = i;
			}		
		}
	}
	if (hasSuit) return ret; //Return the card to be played if one exists
	else return -1; //Return -1 to ploayCard if the suit doenst exist
}

