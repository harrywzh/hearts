/*------------------------
  CS246 - Assignment 6
  "CardPile.cc" 
  hx3zhang | 20437677
  z289wang | 20436476
  Due Date 2012/12/03 
------------------------*/

#include <vector>
#include <algorithm>
#include <iostream>
#include "CardPile.h"
#include "Card.h"

const uint32_t CardPile::DefaultRandomSeed = 37;

CardPile::CardPile() : prng(DefaultRandomSeed) {}


void CardPile::setRandomSeed(uint32_t randomSeed) {
	prng.seed(randomSeed);
}
//set random seed

//destructor
CardPile::~CardPile (){
	for(int i = 0,size = this->size(); i < size ; i++){
		delete (*this)[i];
	}
}
//every element(as a pointer) is deleted

// Other stuff 
//given function for shuffling
void CardPile::shuffle() {
	for (int i = this->size() - 1; i > 0; i--) {
		const int j = prng(i);
		Card* tmp = at(j);
		at(j) = at(i);
		at(i) = tmp;
	}
}

//return the sum of values in the pile
int CardPile::heartsValue(){
	int sum = 0;
	for(int i = 0, size = this->size();i < size;i++){
		sum += (*this)[i]->getHeartsValue();
	}
	return sum;
}

//getter
Card* CardPile::get(int index){
	return ((*this)[index]);
}
//return the index-th element in pile

//pile already in use
int CardPile::getSize(){
	return this->size();
}
//return #elements

