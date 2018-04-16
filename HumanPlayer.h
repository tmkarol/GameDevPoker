#pragma once
#include "Player.h"

class HumanPlayer: public Player {
public:
	HumanPlayer();
	int getBet(Hand, BetHistory, int, int, bool, bool); //get input from user to determine bet amount to give
};