#pragma once
#include "Player.h"

class AlphaPlayer: public Player {
public:
	AlphaPlayer();
	int getBet(Hand, BetHistory, int, int, bool, bool, bool); //makes decision of how much to bet based on current status of game
};