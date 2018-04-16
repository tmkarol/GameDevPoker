#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() {
	srand(time(0)); //seed the RNG once at the beginning to continue to randomly shuffle correctly
	handsPlayed = 1; //first hand is played as 1 instead of 0 to easily output the Hand round currently being played and to calculate when each player leads the betting round
	pot = 0;
}

bool Game::playGame(PlayerType p0, PlayerType p1, int chips0, int chips1, bool reportFlag) {
	cout << endl << "Welcome to Blockhead Poker! Enter 'Q' at any point to quit" << endl << endl;

	//Set the two players to be the correct type 
	if (p0 == HUMAN) {
		playerZero = new HumanPlayer;
	}
	else if (p0 == ALPHA) {
		playerZero = new AlphaPlayer;
	}

	if (p1 == HUMAN) {
		playerOne = new HumanPlayer;
	}

	else if (p1 == ALPHA) {
		playerOne = new AlphaPlayer;
	}

	//Initialize players' chips
	playerZero->setChips(chips0);
	playerOne->setChips(chips1);

	reporting = reportFlag;

	//loop executing game for 20 total hands
	while (handsPlayed <= 20) {
		playAHand();
		++handsPlayed;
		//between each hand, players need to be initialized with a new, empty hand
		Hand newHand;
		playerZero->setHand(newHand);
		playerOne->setHand(newHand);
	}

	//calculate the overall winner
	if (playerZero->getChips() > playerOne->getChips()) {
		cout << "Player one wins!" << endl;
	}

	else if (playerZero->getChips() < playerOne->getChips()) {
		cout << "Player two wins!" << endl;
	}

	else {
		cout << "You tie!" << endl;
	}

	return true;
}


void Game::shuffleDeck() {
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			makeCards("diamonds");
			break;
		case 1:
			makeCards("hearts");
			break;
		case 2:
			makeCards("clubs");
			break;
		case 3:
			makeCards("spades");
			break;
		}
	}

	Card temp;
	for (int k = 0; k < 100000; k++) {
		int j = rand() % deck.size();
		int i = rand() % deck.size();
		temp = deck.at(i);
		deck.at(i) = deck.at(j);
		deck.at(j) = temp;
	}
}

void Game::makeCards(string name) {
	for (int i = 1; i <= 13; i++) {
		int value;
		if (i > 10) {
			value = 10;
		}
		else {
			value = i;
		}
		Card card(name, value);
		deck.push_back(card);
	}
}

void Game::playAHand() {
	cout << "Hand #" << handsPlayed << endl << endl;
	deck.clear();
	history.clearHistory();
	shuffleDeck();
	Card card;
	for (int i = 0; i < 3; ++i) {
		if (i > 0) {
			dealACard(true);
		}
		else {
			dealACard(false);
		}
	}

	playerZero->setChips(playerZero->getChips() - 10);
	playerOne->setChips(playerOne->getChips() - 10);
	pot += 20;

	int firstBetter;
	if (handsPlayed % 2 == 1) {
		firstBetter = 0;
	}
	else {
		firstBetter = 1;
	}
	int bettingResult;

	lastRaise = 0;
	cout << "Betting Round 1:" << endl << endl;
	bettingResult = bettingRound(firstBetter, false);
	if (bettingResult == 1) {
		declareHandWinner(0);
		return;
	}
	else if (bettingResult == 0) {
		declareHandWinner(1);
		return;
	}

	dealACard(true);

	lastRaise = 0;
	cout << endl << "Betting Round 2:" << endl << endl;
	bettingResult = bettingRound(firstBetter, false);
	if (bettingResult == 1) {
		declareHandWinner(0);
		return;
	}
	else if (bettingResult == 0) {
		declareHandWinner(1);
		return;
	}

	dealACard(true);

	lastRaise = 0;
	cout << endl << "Final Betting Round:" << endl << endl;
	bettingResult = bettingRound(firstBetter, true);
	if (bettingResult == 1) {
		declareHandWinner(0);
		return;
	}
	else if (bettingResult == 0) {
		declareHandWinner(1);
		return;
	}

	int winner = compareHands(playerZero->getHand(), playerOne->getHand());
	declareHandWinner(winner);

	return;
}

void Game::dealACard(bool faceUp) {
	Hand p0Hand = playerZero->getHand();
	Hand p1Hand = playerOne->getHand();

	Card card = deck.back();
	card.setFaceUp(faceUp);
	deck.pop_back();

	p0Hand.addCard(card);

	card = deck.back();
	card.setFaceUp(faceUp);
	deck.pop_back();

	p1Hand.addCard(card);

	playerZero->setHand(p0Hand);
	playerOne->setHand(p1Hand);
}

int Game::bettingRound(int firstPlayer, bool lastRound) {
	bool playerZeroCalled = false, playerOneCalled = false, p0canRaise = true, p1canRaise = true;
	int p0Raise, p1Raise, p0RaiseCount = 0, p1RaiseCount = 0;
	while (true) {
		if (p0RaiseCount > 2) {
			p0canRaise = false;
		}
		if (p1RaiseCount > 2) {
			p1canRaise = false;
		}
		if (firstPlayer == 0) {
			p0Raise = playerZero->getBet(playerOne->getHand().getVisible(), history, lastRaise, pot, lastRound, p0canRaise);
			if(p0Raise == -1){
				exit(0);
			}
			pot += p0Raise;
			if (p0Raise == 0) {
				if (lastRaise == 0) {
					playerZeroCalled = true;
				}
				else {
					return 0;
				}
			}
			if (p0Raise == lastRaise) {
				playerZeroCalled = true;
			}
			else {
				Bet newBet(0, p0Raise);
				history.addBet(newBet);
				playerZeroCalled = false;
				++p0RaiseCount;
			}
			lastRaise = p0Raise - lastRaise;

			p1Raise = playerOne->getBet(playerZero->getHand().getVisible(), history, lastRaise, pot, lastRound, p1canRaise);
			if(p1Raise == -1){
				exit(0);
			}
			pot += p1Raise;
			Bet newBetTwo(1, p1Raise);
			history.addBet(newBetTwo);
			if (p1Raise == 0) {
				if (lastRaise == 0) {
					playerOneCalled = true;
				}
				else {
					return 1;
				}
			}
			if (p1Raise == lastRaise) {
				playerOneCalled = true;
			}
			else {
				Bet newBet(0, p1Raise);
				history.addBet(newBet);
				playerOneCalled = false;
				++p1RaiseCount;
			}
			lastRaise = p1Raise - lastRaise;

			if (playerOneCalled && playerZeroCalled) {
				return -1;
			}

		}
		else {
			p1Raise = playerOne->getBet(playerZero->getHand().getVisible(), history, lastRaise, pot, lastRound, p1canRaise);
			if(p1Raise == -1){
				exit(0);
			}
			pot += p1Raise;
			Bet newBet(0, p1Raise);
			history.addBet(newBet);
			if (p1Raise == 0) {
				if (lastRaise == 0) {
					playerOneCalled = true;
				}
				else {
					return 1;
				}
			}
			if (p1Raise == lastRaise) {
				playerOneCalled = true;
			}
			else {
				Bet newBet(0, p1Raise);
				history.addBet(newBet);
				++p1RaiseCount;
				playerOneCalled = false;
			}
			lastRaise = p1Raise - lastRaise;

			p0Raise = playerZero->getBet(playerOne->getHand().getVisible(), history, lastRaise, pot, lastRound, p0canRaise);
			if(p0Raise == -1){
				exit(0);
			}
			pot += p0Raise;
			Bet newBetTwo(1, p0Raise);
			history.addBet(newBetTwo);
			if (p0Raise == 0) {
				if (lastRaise == 0) {
					playerZeroCalled = true;
				}
				else {
					return 0;
				}
			}
			if (p0Raise == lastRaise) {
				playerZeroCalled = true;
			}
			else {
				Bet newBet(0, p0Raise);
				history.addBet(newBet);
				++p0RaiseCount;
				playerZeroCalled = false;
			}
			lastRaise = p0Raise - lastRaise;

			if (playerOneCalled && playerZeroCalled) {
				return -1;
			}

		}
	}
}

int Game::compareHands(Hand lhs, Hand rhs) {
	int leftHand = 0, rightHand = 0;
	for (int i = 0; i < lhs.getCount(); ++i) {
		leftHand += lhs.getCard(i).getCardValue();
		rightHand += rhs.getCard(i).getCardValue();
	}

	if (leftHand > rightHand) {
		return 0;
	}

	else if (rightHand > leftHand) {
		return 1;
	}

	else {
		return -1;
	}

}

void Game::declareHandWinner(int winner) {
	if (winner == 1) {
		playerOne->setChips(playerOne->getChips() + pot);
		pot = 0;
		cout << endl << "Player two wins the hand!" << endl << endl;
	}
	else if(winner == 0){
		playerZero->setChips(playerZero->getChips() + pot);
		pot = 0;
		cout << endl << "Player one wins the hand!" << endl << endl;
	}
	else{
		cout << endl << "It's a tie! Pot gets carried to next round!" << endl << endl;
	}

	cout << "Player One's hand: " << endl;
	playerZero->getHand().print();
	cout << endl << "Player Two's hand: " << endl;
	playerOne->getHand().print();
	cout << endl;
}