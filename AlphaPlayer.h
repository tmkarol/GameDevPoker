#pragma once
#include "Player.h"

class AlphaPlayer: public Player{
	public:
		AlphaPlayer();
		int getBet(Hand, BetHistory, int, int);
};