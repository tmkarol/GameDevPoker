#pragma once
#include "Player.h"

class HumanPlayer: public Player{
	public:
		HumanPlayer();
		int getBet(Hand, BetHistory, int, bool, int);
};