#pragma once
#include "HumanPlayer.h"
#include "AlphaPlayer.h"
#include "BetaPlayer.h"
#include "Card.h"
#include <vector>

class Game {
public:
	Game();
	bool playGame(PlayerType, PlayerType, int, int, bool); //sets up and runs a game of Poker
	void monteCarlo();

private:
	vector<Card> deck; //deck of 52 Card objects
	void makeCards(string); //generates cards for a given suit string
	void shuffleDeck(); //shuffles the Card vector
	void playAHand(bool); //executes card dealing and betting for a single hand
	int bettingRound(int, bool, bool); //receives bets from players and returns results according to whether the player raised, called, or folded
	Player* playerZero; //pointer to a Player object that will either be Human or AI
	Player* playerOne; //pointer to a Player object that will either be Human or AI
	int handsPlayed; //keeps track of how many hands have been played so far
	BetHistory history; //holds the betting history for the current hand
	int lastRaise; //holds the raise amount placed in the previous bet
	int pot; //total chips bet during the hand
	void dealACard(bool); //deals a card to each player
	void declareHandWinner(int, bool); //prints info once a hand has been finished
	//keeps track of number of wins for the players
	int p1Wins; 
	int p2Wins;
};