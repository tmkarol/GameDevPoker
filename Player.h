#pragma once
#include "Hand.h"
#include "BetHistory.h"
#include "PlayerType.h"

class Player{
	public:	
		virtual int getBet(Hand, BetHistory, int, bool, int) = 0;
		void setID(int);
		int getID();
		void setHand(Hand);
		Hand getHand();
		void setChips(int);
		int getChips();
		PlayerType getType();

	protected:
		int id;
		Hand hand;
		int chips;
		PlayerType type;
};