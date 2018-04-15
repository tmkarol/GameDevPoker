#include "Card.h"
#include <string>

using namespace std;

Card::Card(string cardName, int cardVal){
	name = cardName;
	value = cardVal;
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

}