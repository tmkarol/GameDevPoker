#pragma once
#include "PlayerType.h"
#include "HumanPlayer.h"
#include "Card.h"
#include <vector>

class Game{
	public:
		bool playGame(PlayerType, PlayerType, int&, int&, bool);

	private:
		vector<Card> deck;

		void shuffleDeck();

};