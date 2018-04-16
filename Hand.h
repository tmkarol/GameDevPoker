#pragma once
#include "Card.h"
#include <vector>

class Hand {
public:
	Hand();
	void addCard(Card); //add this card to the cards vector
	int getCount(); //returns number of cards in the Hand
	Card getCard(int); //returns a specific card in the Hand
	Hand getVisible(); //returns a new Hand object containing only the cards from the current Hand that are visible
	int evaluateHand(); //returns the total value of the Hand
	void print(); //prints the cards in the Hand

private:
	vector<Card> cards; //vector containing Card objects
};