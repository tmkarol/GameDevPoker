#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(){
	shuffleDeck();
	handsPlayed = 1;
}

bool Game::playGame(PlayerType p0, PlayerType p1, int chips0, int chips1, bool reportFlag){
	if(p0 == HUMAN){
		playerZero = new HumanPlayer;
	}
	else if(p0 == ALPHA){
		playerZero = new AlphaPlayer;
	}

	if(p1 == HUMAN){
		playerOne = new HumanPlayer;
	}

	else if(p1 == ALPHA){
		playerOne = new AlphaPlayer;
	}

	playerZero->setChips(chips0);
	playerOne->setChips(chips1);

	reporting = reportFlag;

	while(handsPlayed <= 20){
		playAHand();
		++handsPlayed;
		playerZero->getHand().clearHand();
		playerOne->getHand().clearHand();
		cout << playerZero->getHand().getCount() << endl;

	}

	if(playerZero->getChips() > playerOne->getChips()){
		cout << "Player one wins!" << endl;
	}

	else if(playerZero->getChips() < playerOne->getChips()){
		cout << "Player two wins!" << endl;
	}

	else{
		cout << "You tie!" << endl;
	}

	return true;
}

void Game::shuffleDeck(){
    for (int i = 0; i < 4; i++) {
        switch(i) {
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
	srand(time(0));
	for(int k = 0; k < 10000; k++) {
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
        if(i > 10){
        	value = 10;
        }
        else{
        	value = i;
    	}
    	Card card(name, value);
        deck.push_back(card);
    }
}

void Game::playAHand(){
	shuffleDeck();
	pot = 20;
	Card card;

	for(int i = 0; i < 3; ++i){
		if(i > 0){
			dealACard(true);
		}
		dealACard(false);
	}

	playerZero->setChips(playerZero->getChips() - 10);
	playerOne->setChips(playerOne->getChips() - 10);

	int firstBetter;
	if(handsPlayed % 2 == 1){
		firstBetter = 0;
	}
	else{
		firstBetter = 1;
	}
	bettingRound(firstBetter);

	dealACard(true);
	
}

void Game::dealACard(bool faceUp){
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

void Game::bettingRound(int firstPlayer){
	if(firstPlayer == 0){
		lastRaise = playerZero->getBet(playerOne->getHand().getVisible(), history, lastRaise, pot);
		pot += lastRaise;
		Bet newBet(0, lastRaise);
		history.addBet(newBet);
		lastRaise = playerOne->getBet(playerZero->getHand().getVisible(), history, lastRaise, pot);
		pot += lastRaise;
	}
	else{
		lastRaise = playerOne->getBet(playerZero->getHand().getVisible(), history, lastRaise, pot);
		pot += lastRaise;
		Bet newBet(0, lastRaise);
		history.addBet(newBet);
		lastRaise = playerZero->getBet(playerOne->getHand().getVisible(), history, lastRaise, pot);
		pot += lastRaise;
	}
}