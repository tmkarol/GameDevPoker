#include "Card.h"
#include <vector>

class Hand{
	public:
		void clearHand();
		void addCard(Card);
		int getCount();
		Card getCard(int);
		Hand getVisible();
		int evaluateHand();

	private:
		vector<Card> cards;
};	