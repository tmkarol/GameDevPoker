#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() {
	srand(time(0)); //seed the RNG once at the beginning to continue to randomly shuffle correctly
	handsPlayed = 1; //first hand is played as 1 instead of 0 to easily output the Hand round currently being played and to calculate when each player leads the betting round
	pot = 0;
	p1Wins = 0;
	p2Wins = 0;
}

void Game::monteCarlo() {
	int numGames = 0;
	cout << "How many games would like the AIs to play? ";
	cin >> numGames;
	for(int i = 0; i < numGames; ++i){
		pot = 0;
		handsPlayed = 1;
		playGame(ALPHA, BETA, 1000, 1000, false);
	}
	cout << "Alpha player won " << p1Wins << " games! Average: ";
	if(p1Wins > 0){
		cout << ((double)p1Wins / (double)numGames) * 100 << "%" << endl;
	}
	else if(p1Wins == numGames){
		cout << "100%" << endl;
	}
	else{
		cout << "0%" << endl;
	}
	cout << "Beta player won " << p2Wins << " games! Average: ";
	if(p2Wins > 0){
		cout << ((double)p2Wins / (double)numGames) * 100 << "%" << endl;
	}
	else if(p2Wins == numGames){
		cout << "100%" << endl;
	}
	else{
		cout << "0%" << endl;
	}
}

bool Game::playGame(PlayerType p0, PlayerType p1, int chips0, int chips1, bool reportFlag) {
	if (reportFlag) {
		cout << endl << "Welcome to Blockhead Poker! Enter 'Q' at any point to quit" << endl << endl;
	}

	//Set the two players to be the correct type
	if (p0 == HUMAN) {
		playerZero = new HumanPlayer;
	}
	else if (p0 == ALPHA) {
		playerZero = new AlphaPlayer;
	}
	else if (p0 == BETA) {
		playerZero = new BetaPlayer;
	}

	if (p1 == HUMAN) {
		playerOne = new HumanPlayer;
	}

	else if (p1 == ALPHA) {
		playerOne = new AlphaPlayer;
	}
	else if (p1 == BETA) {
		playerOne = new BetaPlayer;
	}

	//Initialize players' chips
	playerZero->setChips(chips0);
	playerOne->setChips(chips1);

	Hand *newOneHand = new Hand(), *newTwoHand = new Hand();
	playerZero->setHand(*newOneHand);
	playerOne->setHand(*newTwoHand);


	//loop executing game for 20 total hands
	while (handsPlayed <= 20) {
		playAHand(reportFlag);
		++handsPlayed;
		//between each hand, players need to be initialized with a new, empty hand
		playerZero->setHand(*newOneHand);
		playerOne->setHand(*newTwoHand);
	}

	//calculate the overall winner
	if (playerZero->getChips() > playerOne->getChips()) {
		if (reportFlag) {
			cout << "You win!" << endl;
		}
		++p1Wins;
	}

	else if (playerZero->getChips() < playerOne->getChips()) {
		if (reportFlag) {
			cout << "AI wins!" << endl;
		}
		++p2Wins;
	}

	else {
		if (reportFlag) {
			cout << "You tie!" << endl;
		}
	}

	return true;
}


void Game::shuffleDeck() {
	//call function to generate the cards for each suit, cards must be generated every time deck is shuffled since cards are taken out of the deck during the hand
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

	//shuffle the cards in the deck
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
	//create 13 cards for the suit and add to the deck vector
	for (int i = 1; i <= 13; i++) {
		int value;
		//all cards above 10 will have a value of 10
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

void Game::playAHand(bool reportFlag) {
	if (reportFlag) {
		cout << "Hand #" << handsPlayed << endl << endl;
	}

	deck.clear(); //since deck will be regenerated, empty the cards that are left from the previous hand
	history.clearHistory(); //clear the betting history from the previous hand
	shuffleDeck(); //regenerate and shuffle deck

	//deal three cards to each player
	for (int i = 0; i < 3; ++i) {
		//last two cards are face up
		if (i > 0) {
			dealACard(true);
		}
		else {
			dealACard(false);
		}
	}

	//each player puts 10 chips in the pot to buy in
	playerZero->setChips(playerZero->getChips() - 10);
	playerOne->setChips(playerOne->getChips() - 10);
	pot += 20;

	//calculate which player will begin the betting rounds based on how many hands have been played
	int firstBetter;
	if (handsPlayed % 2 == 1) {
		firstBetter = 0;
	}
	else {
		firstBetter = 1;
	}

	int bettingResult;
	lastRaise = 0; //initialize the lastRaise to 0 before the betting round
	if (reportFlag) {
		cout << "Betting Round 1:" << endl << endl;
	}

	bettingResult = bettingRound(firstBetter, false, reportFlag);
	//if the second player folded, first player wins the hand
	if (bettingResult == 1) {
		declareHandWinner(0, reportFlag);
		return;
	}
	//if first player folded, second player wins the hand
	else if (bettingResult == 0) {
		declareHandWinner(1, reportFlag);
		return;
	}

	//each player is dealt another card faceup
	dealACard(true);

	lastRaise = 0;//initialize last raise before betting round
	if (reportFlag) {
		cout << endl << "Betting Round 2:" << endl << endl;
	}

	bettingResult = bettingRound(firstBetter, false, reportFlag);
	if (bettingResult == 1) {
		declareHandWinner(0, reportFlag);
		return;
	}
	else if (bettingResult == 0) {
		declareHandWinner(1, reportFlag);
		return;
	}

	dealACard(true);

	lastRaise = 0;
	if (reportFlag) {
		cout << endl << "Final Betting Round:" << endl << endl;
	}

	bettingResult = bettingRound(firstBetter, true, reportFlag);
	if (bettingResult == 1) {
		declareHandWinner(0, reportFlag);
		return;
	}
	else if (bettingResult == 0) {
		declareHandWinner(1, reportFlag);
		return;
	}

	//if no one folded at this point, the winner is whoever has a higher value hand
	if (playerZero->getHand().evaluateHand() > playerOne->getHand().evaluateHand()) {
		declareHandWinner(0, reportFlag);
	}
	else if (playerOne->getHand().evaluateHand() > playerZero->getHand().evaluateHand()) {
		declareHandWinner(1, reportFlag);
	}
	else {
		declareHandWinner(-1, reportFlag);
	}

	return;
}

void Game::dealACard(bool faceUp) {
	//get players' hand objects to be able to add a Card object to them
	Hand p1Hand, p0Hand;
	p0Hand = playerZero->getHand();
	p1Hand = playerOne->getHand();



	//add the next card in the deck to the hand and remove that card from the deck
	Card card = deck.back();
	card.setFaceUp(faceUp); //if the card is faceUp, set it accordingly
	deck.pop_back();
	p0Hand.addCard(card);

	card = deck.back();
	card.setFaceUp(faceUp);
	deck.pop_back();
	p1Hand.addCard(card);

	//set the players' hands to the new hands that have the new card dealt
	playerZero->setHand(p0Hand);
	playerOne->setHand(p1Hand);
}

int Game::bettingRound(int firstPlayer, bool lastRound, bool reportFlag) {
	//variables monitor whether players have called, how many times they have raised and how much they raise during the round
	bool playerZeroCalled = false, playerOneCalled = false, p0canRaise = true, p1canRaise = true;
	int p0Raise, p1Raise, p0RaiseCount = 0, p1RaiseCount = 0;

	//loop will continue until both players call or one folds
	while (true) {
		//if either player has raised 3 times, they will no longer be able to during the round
		if (p0RaiseCount > 2) {
			p0canRaise = false;
		}
		if (p1RaiseCount > 2) {
			p1canRaise = false;
		}

		//if the first player gets to start the betting rounds
		if (firstPlayer == 0) {
			p0Raise = playerZero->getBet(playerOne->getHand().getVisible(), history, lastRaise, pot, lastRound, p0canRaise, reportFlag);
			//if the response is a -1, the player would be a human player signaling to quit the game
			if (p0Raise == -1) {
				exit(0);
			}

			//add whatever was raised to the pot
			pot += p0Raise;

			//if raise was a 0, could either be a check or a fold
			if (p0Raise == 0) {
				//if there was no previous raise, this is a check
				if (lastRaise == 0) {
					playerZeroCalled = true;
				}
				//otherwise first player folded
				else {
					return 0;
				}
			}

			//if the raise is the same as the previous raise, the player called
			if (p0Raise == lastRaise) {
				playerZeroCalled = true;
			}

			//otherwise, the player decided to raise
			else {
				Bet newBet(0, p0Raise);
				history.addBet(newBet); //add this bet to the history
				playerZeroCalled = false;
				++p0RaiseCount; //increment the raise count for this player
			}

			//set this raise as previous before the next player's turn (the new raise is the amount given over the previous raise)
			lastRaise = p0Raise - lastRaise;

			//check to see if both players have called yet and if they have, end the betting round
			if (playerOneCalled && playerZeroCalled) {
				return -1;
			}

			//next player events mimic the first player's events
			p1Raise = playerOne->getBet(playerZero->getHand().getVisible(), history, lastRaise, pot, lastRound, p1canRaise, reportFlag);
			if (p1Raise == -1) {
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

		//if the second player starts the betting round (code is same, just in reverse, which I know is bad but I couldn't think of an easier way to do it)
		else {
			p1Raise = playerOne->getBet(playerZero->getHand().getVisible(), history, lastRaise, pot, lastRound, p1canRaise, reportFlag);
			if (p1Raise == -1) {
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

			p0Raise = playerZero->getBet(playerOne->getHand().getVisible(), history, lastRaise, pot, lastRound, p0canRaise, reportFlag);
			if (p0Raise == -1) {
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

void Game::declareHandWinner(int winner, bool reportFlag) {
	//give player the chips and output a message depending on the winner
	if (winner == 1) {
		playerOne->setChips(playerOne->getChips() + pot);
		pot = 0;
		if (reportFlag) {
			cout << endl << "AI wins the hand!" << endl << endl;
		}
	}
	else if (winner == 0) {
		playerZero->setChips(playerZero->getChips() + pot);
		pot = 0;
		if (reportFlag) {
			cout << endl << "You win the hand!" << endl << endl;
		}
	}
	else {
		if (reportFlag) {
			cout << endl << "It's a tie! Pot gets carried to next round!" << endl << endl;
		}
	}
	if (reportFlag) {
		//output all of the cards in both players' hands
		cout << "Your hand: " << endl;
		playerZero->getHand().print();
		cout << endl << "AI's hand: " << endl;
		playerOne->getHand().print();
		cout << endl;
	}
}