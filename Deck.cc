/*------------------------
  CS246 - Assignment 6
  "Deck.cc" 
  hx3zhang | 20437677
  z289wang | 20436476
  Due Date 2012/12/03 
------------------------*/

#include "Deck.h"
#include "Player.h"
#include <cstdlib>

// Constructor creates an empty deck.
Deck::Deck () : CardPile::CardPile() {}

// Take an existing (ideally, empty) deck and fill it with the
// usual suspects of 52 cards by iterating through the elements of
// Card::Rank and Card::Suit.
void Deck::generate(){
	for(int i = 0;i < 4; i++){
		for(int j = 0;j < 13; j++){
			Card::Rank r = static_cast<Card::Rank>(j);
			Card::Suit s = static_cast<Card::Suit>(i);
			Card* aCard = new Card(r,s);
			this->push_back(aCard);
		}
	}
}
// Check that the deck of cards does indeed contain the usual
// 52 suspects; this isn't hard if you know your STL containers.
bool Deck::playingWithAFullDeck () const{
	int contained[52];
	for(int i = 0; i < 52 ;i++){
		contained[i] = 0;
	}
	if(this->size() != 52) return false;
	for(int i = 0; i < 52; i++){
		Card c = *((*this)[i]);
		int r = static_cast<int>(c.getRank());
		int s = static_cast<int>(c.getSuit());
		contained[s * 13 + r] ++;
	}
	for(int i = 0; i< 52;i++){
		if(contained[i] != 1){
			return false;
		}
	}
	return true;
}

//deck has 52 cards
void Deck::print(){
	cout << "   ";
	for(int i = 0, size = this->size(); i < size ; i++){
		cout << " " << (*(*this)[i]);
	}
	cout << endl;
}
//print the deck with space as prefix,space as delimiter and a endl as subfix

//c is not null
void Deck::add(Card* c){
	this->push_back(c);
}
//put c to the top of deck

//players has 4 elements
void Deck::deal(Player* p1, Player* p2, Player* p3, Player* p4){
	Player* players [4] = {p1, p2, p3, p4};
	for(int i = 51;i > -1 ;i--){
		int j = 3 - (i % 4);
		players[j]->draw(this->at(i));
	}
}
//deal the cards to players

//the deck is no longer in use
void Deck::clear(){
	for(int i = 51;i > -1;i--){
		Card* tmp = this->at(i);
		delete tmp;
		this->pop_back();
	}
}
//empty deck

// Take an existing (ideally, empty) deck and read in 52 cards from the
// indicated input stream, making use of operator>>(istream&, Card&).
// Make sure that you are playingWithAFullDeck at the end.
// The ordering should be so that the last card read in will be on the top
// of the deck.
istream& operator>> (istream& in, Deck& deck){
	Card* tmp;
	for(int i = 0; i < 52; i++){
		tmp = new Card();
		in >> (*tmp);
		deck.add(tmp);
	}
	if( !deck.playingWithAFullDeck() ){
		exit(EXIT_FAILURE);
	}
	return in;
}
