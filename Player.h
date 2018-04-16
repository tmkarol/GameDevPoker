#pragma once
#include "Hand.h"
#include "BetHistory.h"
#include "PlayerType.h"

class Player {
public:
	Player();
	virtual int getBet(Hand, BetHistory, int, int, bool, bool) = 0; //abstract function to be implemented by child types
	void setHand(Hand);//assigns Hand object to player
	Hand getHand();//returns the Hand object belonging to the player
	void setChips(int);//assigns chip amount to player
	int getChips();//returns amount of chips belonging to player

protected:
	Hand hand; //Hand of cards belonging to the player
	int chips; //chips belonging to the player

};