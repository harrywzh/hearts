/*------------------------
  CS246 - Assignment 6
  "trick.cc" 
  hx3zhang | 20437677
  z289wang | 20436476
  Due Date 2012/12/03 
------------------------*/

#include "Card.h" 
#include <sstream>
#include "Trick.h"

using namespace std;

//Constructor - Initilizes Variables
Trick::Trick(){
	turn = 0;
	value = 0;
	contents = "";
}

//addcard - Card* int -> int
//Takes a card and a player, and adds it to the trick. Returns the rank of the highest card of correct suit in the trick.
int Trick::addCard(Card* c, int pid){
	stringstream ss;
	//Update highcard and winnner if (shortcircuit logic):
	//It is the first turn of the trick OR
	//Card c followed suit and is larger than the highcard
	if (turn == 0 || ((c->getSuit() == highCard->getSuit()) && (*highCard < *c))){
		highCard = c;
		winner = pid;
	}
	//Adds the hearts value of the card
	value += c->getHeartsValue();
	ss << " " << *c;
	//Adds the card to an output string
	contents += ss.str();
	turn++;
	return highCard->getRank(); 
}

//In the implementation, for each Trick object, addCard is called 4 times, and the functions below are only called after 4 cards have been added


//Get the winner of the trick (0-3)
int Trick::getWinner() const{
	return winner;
}
//Get the hearts value of the trick
int Trick::getValue() const{
	return value;
}
//Get the string representing the cards in the trick (removing the first whitespace)
string Trick::getCards() {
	return contents.substr(1);
}
