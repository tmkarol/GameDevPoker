#include "Hand.h"
#include <iostream>

using namespace std;

Hand::Hand() {

}

void Hand::addCard(Card card) {
	cards.push_back(card);
}

int Hand::getCount() {
	return cards.size();
}

Card Hand::getCard(int index) {
	return cards.at(index);
}

Hand Hand::getVisible() {
	Hand visible;
	//loop through cards in this Hand object and add only visible ones to the new object
	for (int i = 0; i < cards.size(); ++i) {
		if (cards.at(i).isFaceUp()) {
			visible.addCard(cards.at(i));
		}
	}

	return visible;
}

int Hand::evaluateHand() {
	int total = 0;
	//loop through cards and total their values
	for (int i = 0; i < cards.size(); ++i) {
		total += cards.at(i).getCardValue();
	}
	return total;
}

void Hand::print() {
	for (int i = 0; i < cards.size(); ++i) {
		cout << cards.at(i).getCardValue() << " of " << cards.at(i).getCardName() << endl;
	}
}