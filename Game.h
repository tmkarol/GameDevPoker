#pragma once
#include "HumanPlayer.h"
#include "AlphaPlayer.h"
#include "Card.h"
#include <vector>

class Game{
	public:
		Game();
		bool playGame(PlayerType, PlayerType, int, int, bool);

	private:
		vector<Card> deck;
		void makeCards(string);
		void shuffleDeck();
		void playAHand();
		void bettingRound(int);

		Player* playerZero;
		Player* playerOne;
		bool reporting;
		int handsPlayed;
		BetHistory history;
		int lastRaise;
		int pot;
		void dealACard(bool);
};