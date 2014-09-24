#ifndef _CARDPILE_H_
#define _CARDPILE_H_

using namespace std;

#include <vector>
#include "Card.h"
#include "PRNG.h"

class CardPile : protected vector<Card*> {
    public:
	// Constructors and destructor
	CardPile ();
	virtual ~CardPile ();

	void setRandomSeed(uint32_t randomSeed);
	// Other stuff needed
	void shuffle();
	int heartsValue();

    protected:
	//getters
	Card* get(int index);
	int getSize();

    private:
	PRNG prng;
	static const uint32_t DefaultRandomSeed;
};

#endif

