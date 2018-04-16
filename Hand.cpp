#include "Hand.h"
#include <iostream>

using namespace std;

Hand::Hand(){

}

void Hand::clearHand(){
	cards.clear();
}

void Hand::addCard(Card card){
	cards.push_back(card);
}

int Hand::getCount(){
	return cards.size();
}

Card Hand::getCard(int index){
	return cards.at(index);
}

Hand Hand::getVisible(){
	Hand visible;
	for(int i = 0; i < cards.size(); ++i){
		if(cards.at(i).isFaceUp()){
			visible.addCard(cards.at(i));
		}
	}

	return visible;
}

int Hand::evaluateHand(){
	int total;
	for(int i = 0; i < cards.size(); ++i){
		total += cards.at(i).getCardValue();
	}
	return total;
}

void Hand::print(){
	for(int i = 0; i < cards.size(); ++i){
		cout << cards.at(i).getCardValue() << " of " << cards.at(i).getCardName() << endl;
	}
}