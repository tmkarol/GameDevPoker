#pragma once
#include <string>

using namespace std;
class Card {
public:
	Card();
	Card(string, int);
	string getCardName();
	int getCardValue();
	bool isFaceUp();
	void setFaceUp(bool);

private:
	string name;
	int value;
	bool faceUp; //signifies whether the card is visible to other players
};