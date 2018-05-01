#pragma once
#include "Player.h"

class BetaPlayer: public Player{
public:
	BetaPlayer();
	int getBet(Hand, BetHistory, int, int, bool, bool, bool); //makes decision of how much to bet based on current status of game, but better than Alpha AI
};