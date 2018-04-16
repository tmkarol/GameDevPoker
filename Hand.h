#pragma once
#include "Card.h"
#include <vector>

class Hand{
	public:
		Hand();
		void clearHand();
		void addCard(Card);
		int getCount();
		Card getCard(int);
		Hand getVisible();
		int evaluateHand();
		void print();

	private:
		vector<Card> cards;
};	