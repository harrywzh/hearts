/*------------------------
  CS246 - Assignment 6
  "RandomPlayer.cc" 
  hx3zhang | 20437677
  z289wang | 20436476
  Due Date 2012/12/03 
------------------------*/

#include <string>
#include "Player.h"
#include "RandomPlayer.h"

using namespace std;

//lead, throwOff, and followSuit
//These functions are called from Player::playCard. They return an integer value (not a Card or Card*), representing the relative location of the 
//card to be played in the player's hand. playCard will then retrieve the card and pass it back to the main program.

//constructor
RandomPlayer::RandomPlayer(string name) : Player::Player(name){}

//constructor
RandomPlayer::RandomPlayer(string name,int seed) : Player::Player(name){
	this->name = 'r' + this->name;
	prng.seed(seed); //Creates prng with specified seed
}
//add prefix

//lead - returns the nth card, n being random
int RandomPlayer::lead(){
	return prng(0,hand.size()-1);	
} 
//throwOff - returns the nth card, n being random
int RandomPlayer::throwOff(){
	return prng(0,hand.size()-1);	
}

//followSuit - returns the nth card of the correct suit, n being random
int RandomPlayer::followSuit(int highRank, int suit){
	vector<int> ofSuit; //Takes the locations of all the cards of the correct suit and stores it in a vector
	for (unsigned int i = 0; i < hand.size(); i++){
		if (hand[i]->getSuit() == suit) ofSuit.push_back(i);
	}
	if (ofSuit.empty()) return -1; //If no cards of suit, then return -1 to playCard
	
	return ofSuit[prng(0,ofSuit.size()-1)]; //Else return the nth card 
	
}
