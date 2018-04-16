#include "BetHistory.h"

void BetHistory::clearHistory() {
	bets.clear();
}

void BetHistory::addBet(Bet bet) {
	bets.push_back(bet);
}

int BetHistory::getCount() {
	return bets.size();
}
