/*------------------------
  CS246 - Assignment 6
  "HumanPlayer.cc" 
  hx3zhang | 20437677
  z289wang | 20436476
  Due Date 2012/12/03 
------------------------*/

#include <string>
#include <sstream>
#include "Player.h"
#include "HumanPlayer.h"

using namespace std;

//lead, throwOff, and followSuit
//These functions are called from Player::playCard. They return an integer value (not a Card or Card*), representing the relative location of the 
//card to be played in the player's hand. playCard will then retrieve the card and pass it back to the main program.

//constructor
HumanPlayer::HumanPlayer(string name) : Player::Player(name){
	this->name = 'h' + this->name;
}
//add prefix


//lead and throwOff pass -1 as suit as suit doesnt matter, followsuit passes the suit that must be enforcded
int HumanPlayer::lead(){
	return interact(-1);	
}
int HumanPlayer::throwOff(){
	return interact(-1);
}
int HumanPlayer::followSuit(int highRank, int suit){
	return interact(suit);
}

//interact - int -> int
//Main function to handle interactive play for the human player
//Returns the location of the card that the human has picked
int HumanPlayer::interact(int suit){
	
	cout << "Human player " << name << " has these cards:" << endl;
	cout << printHand(); //Show current cards
	Card c;
	string strin;
	
	while(true){ //Loop to ensure correct input - terminated upon return value
		
		bool notInHand = true;
		cout << endl << "What card would you like to play, " << name << "? ";
		cin >> strin;
		//Check if it is a legal input (a card)
		if (Card::stringIsALegalCard(strin)){
			stringstream ss;
			ss << strin;
			ss >> c;
			//Store value as a card object
			for (unsigned int i = 0; i < hand.size(); i++){
				if (c == *hand[i]){
					//If the player has that card, and its the right suit (or if suit doesnt matter) then return its location
					if (suit == -1 || c.getSuit()==suit) return i;
					else {
					//If its not the right suit, enforce to follow suit
						cout << "You have at least one ";
						switch(suit){
						//This is required as there is no easy way to map a suit's enum value to a character without directly accessing Card's internal functions
							case 0: cout << "S";
							break;
							case 1: cout << "D";
							break;
							case 2: cout << "C";
							break;
							case 3: cout << "H";
							break;
						} //switch
						cout << "; You must follow suit!";
						notInHand = false;
						
					} //if
				} //if
			} //for
			//If the player doesn't have the card
			if (notInHand) cout << c << " is not in your hand";
		} else {
		//When the input is not a valid card
			cout << strin << " is not a card";
		} //if
			
		
	} //while
}
