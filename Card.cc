/*------------------------
  CS246 - Assignment 6
  "Card.cc" 
  hx3zhang | 20437677
  z289wang | 20436476
  Due Date 2012/12/03 
------------------------*/

#include <string>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "Card.h"

using namespace std;
/*
 * 	// Takes a char string of length 2, which better be legal
	Card (string sCard);

	// Accessor fcns
	Rank getRank () const;
	Suit getSuit () const;
	int getHeartsValue () const;

	// Static utility function to check if a two char string
	// represents a legal card value
	static bool stringIsALegalCard (string s);
 */
const string Card::RankName = "23456789TJQKA";
const string Card::SuitName = "SDCH";
const int Card::numRanks = RankName.length();
const int Card::numSuits = SuitName.length();
const int Card::numCards = Card::numRanks * Card::numSuits;
const Card Card::TwoOfClubs (Card::Two, Card::Clubs);
const Card Card::QueenOfSpades (Card::Queen, Card::Spades);

// We'll give you this one.
Card::Card() : rank(Ace), suit(Spades) {}

//constructor
Card::Card (Rank r, Suit s) : rank(r), suit(s) {}
//set rank and suit

////copy constructor
Card::Card(string sCard){
	int index;// index in Rank & Suit
	if(!Card::stringIsALegalCard(sCard)){
		exit(EXIT_FAILURE);
	}
	index = Card::RankName.find(sCard[0],0);
	this->rank = static_cast<Card::Rank>(index);
	index = Card::SuitName.find(sCard[1],0);
	this->suit = static_cast<Card::Suit>(index);
}
//copy scard by value

//destructor
Card::~Card(){}

//getter for rank
Card::Rank Card::getRank() const{
	return this->rank;
}
//return the rank

//getter for suit
Card::Suit Card::getSuit() const{
	return this->suit;
}
//return suit

//setter for rank
void Card::setRank(Rank r){
	this->rank = r;
}
//set rank to r

//setter for suit
void Card::setSuit(Suit s){
	this->suit = s;
}
//set suit to s

/*
 * Card::heartsValue of a given card is 1 if the card is a heart, 13 if the card is
the Queen of Spades, and 0 if it is any other card. The Jack of Diamonds has no
special value for us, though it does in some variants of the game.
 */
int Card::getHeartsValue () const{
	if(this->getSuit() == Card::Hearts){
		return 1;
	}else if((this->getSuit() == Card::Spades) && (this->getRank() == Card::Queen)){
		return 13;
	}
	return 0;
}

/*
 * Card::stringIsALegalCard(string) should return true iff the string parameter is
two characters long and the first char is a legal rank name and the second char
is a legal suit name.
 */
bool Card::stringIsALegalCard (string s){
	return (s.length() == 2) &&
			(Card::RankName.find(s[0],0) != string::npos) &&
			(Card::SuitName.find(s[1],0) != string::npos);
}
//return whether the card is legal

//equal operator
bool operator== (const Card& c1, const Card& c2){
	return c1.getRank() == c2.getRank() &&
			c1.getSuit() == c2.getSuit();
}
//return whether 2 cards are equal

//less operator for card value
bool operator< (const Card& c1, const Card& c2){
	int val1,val2;// the value of c1 and c2 for the purpose of comparison
	val1 = static_cast<int>(c1.getRank());
	val2 = static_cast<int>(c2.getRank());
	if(val1 < val2 ){
		return true;
	}else if(val1 > val2){
		return false;
	}else{
		val1 = static_cast<int>(c1.getSuit());
		val2 = static_cast<int>(c2.getSuit());
		return val1 < val2;
	}
}
/*
 * c1<c2 if c1's rank is less than c2's or they have the same rank, but
c1's suit is less than c2's. Use the rank and suit ordering implied by the enum
types.
 */

//output operator
ostream& operator<< (ostream &out, const Card &c){
	//index is the corresponding index of card in card constant string
	int index = static_cast<int>(c.getRank());
	out << Card::RankName[index];
	index = static_cast<int>(c.getSuit());
	out << Card::SuitName[index];
	return out;
}
/*
 * the idea is:
 * operator<< on a Card should print "9H" if the card is the Nine of Hearts.
 */

//input operator
istream& operator>> (istream& in, Card& card){
	string strc;//to store the card
	int index1 = -1,index2 = -1;// to store the index of cc in card constant string
	in >> strc;
	if( strc.length() == 2){
		index1 = Card::RankName.find(strc[0],0);
		index2 = Card::SuitName.find(strc[1],0);
	}
	if( index1 < 0 || index2 < 0){
		cerr << "Error, " << strc << " is not a legal card. Aborting." << endl;
		exit(EXIT_FAILURE);
	}
	card.setRank(static_cast<Card::Rank>(index1));
	card.setSuit(static_cast<Card::Suit>(index2));
	return in;
}
/*
 * For operator>>, the input is a string of length 2 of the form "9H" (if the card
is the Nine of Hearts).
 */
