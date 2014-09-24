/*------------------------
  CS246 - Assignment 6
  "Player.cc" 
  hx3zhang | 20437677
  z289wang | 20436476
  Due Date 2012/12/03 
------------------------*/


#include "Card.h"
#include "vector"
#include "Player.h" 
#include <string>
#include <sstream>
using namespace std;

//contructors
Player::Player(){}

Player:: Player(string name) : name(name) {
	points = 0;	
}

//destructor
Player::~Player(){}

//hand is fulfilled
string Player::printHand(){
	stringstream ss;
	ss << "   ";
	for(int i = 0, size = hand.size(); i < size ; i++){
		ss << " " << *(hand[i]);
	}
	return ss.str();
}
//print hand cards

//return players name

//c is a valid card
void Player::draw(Card* c){
	hand.push_back(c);
}
//c is put on the top of playes hand

//Get the current score of the player
int Player::getScore() const{
	return points;
}

//Get the name of Player
string Player::getName() const{
	return name;
}

//Add points to the player
void Player::addPoints(int val){
	points += val;
}

//playCard - int int -> Card*
//Determines which card from a player-derived class is to be played and returns a pointer to it
//Preconditions -The main program determines a player needs to play a card, and provides the current high rank and trump suit
//Postcondition -A pointer to a Card object is returned to the main program, the pointer in the player's hand is removed
Card* Player::playCard(int highRank, int suit){
	int location; //Stores the location of the card to be played in the hand
	
	//Suit uses values form the enum, in addtion to -2 (First card, 2 of clubs) and -1 (leading)
	if (suit == -2){ //Leading two of clubs
		for (int i = 0; i < hand.size(); i++){
			if (*hand[i] == hand[i]->TwoOfClubs) location = i;
		}
		cout << "  " << name << " has 2C and leads with it" << endl;
	
	//The suit is irrelevant if it is a lead card. The child class's lead function is called	
	} else if (suit == -1){
		location = this->lead();
		cout << "  " << name << " led " << *hand[location] << endl;
	} else {
	//Calls follow suit, which either returns the location of the card in a player's hand, or -1, meaning the player doesn't have that suit
		location = this->followSuit(highRank, suit);
		if (location == -1){
		//Calls throwOff if the player doesn't have the suit
			location = this->throwOff();
			cout << "  " << name << " threw off " << *hand[location] << endl;
		} else {
			cout << "  " << name << " followed suit with " << *hand[location] << endl;
		}
	}
	
	//The pointer to the card is returned and erased from the player's hand
	Card* c = hand[location];
	hand.erase (hand.begin() + location);
	return c;
	
}








