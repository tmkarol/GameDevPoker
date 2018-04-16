#pragma once
#include "Hand.h"
#include "BetHistory.h"
#include "PlayerType.h"

class Player{
	public:	
		Player();
		virtual int getBet(Hand, BetHistory, int, int, bool, bool) = 0;
		void setHand(Hand);
		Hand getHand();
		void setChips(int);
		int getChips();
		PlayerType getType();

	protected:
		Hand hand;
		int chips;
		PlayerType type;

};