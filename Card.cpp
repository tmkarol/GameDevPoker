#include "Card.h"
#include <string>

using namespace std;

Card::Card(){
	faceUp = false;
}

Card::Card(string cardName, int cardVal){
	name = cardName;
	value = cardVal;
	faceUp = false;
}

string Card::getCardName(){
	return name;
}

int Card::getCardValue(){
	return value;
}

bool Card::isFaceUp(){
	return faceUp;
}

void Card::setFaceUp(bool isFaceUp){
	faceUp = isFaceUp;
}