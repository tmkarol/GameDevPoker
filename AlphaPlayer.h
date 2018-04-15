#pragma once
#include "Player.h"

class AlphaPlayer: public Player{
	public:
		int getBet(Hand, BetHistory, int, bool, int);
};