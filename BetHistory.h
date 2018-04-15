#pragma once
#include "Bet.h"
#include <vector>

using namespace std;
class BetHistory{
	public:
		void clearHistory();
		void addBet(Bet);
		int getCount();
		Bet getBet(int);

	private:
		vector<Bet> bets;
};