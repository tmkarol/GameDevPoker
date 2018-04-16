#pragma once
#include "Bet.h"
#include <vector>

using namespace std;
class BetHistory {
public:
	void clearHistory(); //clears bet vector
	void addBet(Bet); //adds Bet object to vector of bets
	int getCount(); //returns size of bets vector

private:
	vector<Bet> bets;
};