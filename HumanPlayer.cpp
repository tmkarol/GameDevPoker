#include "HumanPlayer.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer() {
}

int HumanPlayer::getBet(Hand opponent, BetHistory bh, int bet2player, int pot, bool lastRound, bool canRaise) {
	char decision, raiseChar;
	int raise;

	//show player's hand
	cout << "Here are your cards:" << endl;
	hand.print();

	//show opponent's visible hand
	cout << endl << "Here is your opponents visible cards:" << endl;
	opponent.print();

	//output other info about the status of the round
	cout << endl << "The current raise is: " << bet2player << endl;
	cout << "the pot contains: " << pot << " chips" << endl;
	cout << "You have " << chips << " chips" << endl;

	//if the user has raised 3 times, they cannot raise anymore
	if (!canRaise) {
		cout << "You can't raise anymore! Would you like to call or fold? (Enter C or F) ";
		cin >> decision;
		cout << endl;
		//if user enters 'Q', signal to game engine that the user would like to quit
		if (decision == 'Q') {
			return -1;
		}
		//if user puts in a different character, show error message and give them another try
		while (decision != 'C' && decision != 'F') {
			cout << "Must pick a valid option! (Enter C or F) ";
			cin >> decision;
			cout << endl;
			if (decision == 'Q') {
				return -1;
			}
		}
	}
	//if there isn't a previous raise, player can only raise or call
	else if (bet2player == 0) {
		cout << "Would you like to raise or call? (Enter R or C) ";
		cin >> decision;
		cout << endl;
		if (decision == 'Q') {
			return -1;
		}
		while (decision != 'C' && decision != 'R') {
			cout << "Must pick a valid option! (Enter R or C) ";
			cin >> decision;
			cout << endl;
			if (decision == 'Q') {
				return -1;
			}
		}
	}
	//otherwise, player has all options
	else {
		cout << "Would you like to raise, call or fold? (Enter R, C or F) ";
		cin >> decision;
		cout << endl;
		if (decision == 'Q') {
			return -1;
		}
		while (decision != 'C' && decision != 'F' && decision != 'R') {
			cout << "Must pick a valid option! (Enter R, C or F) ";
			cin >> decision;
			cout << endl;
			if (decision == 'Q') {
				return -1;
			}
		}
	}
	//if user wants to raise, ask for input amount between 1 and 10 and subtract the amount from the player's chips
	if (decision == 'R') {
		cout << "How much would you like to raise? (Max raise is 10) ";
		cin >> raise;
		cout << endl;
		while (raise > 10 || raise < 1) {
			cout << "Must raise amount between 1 and 10 ";
			cin >> raise;
			cout << endl;
		}
		chips -= raise;
		return raise;
	}
	//if user wants to call, subtract the previous raise from the player's chips
	else if (decision == 'C') {
		chips -= bet2player;
		return bet2player;
	}
	//if user wants to fold, send back a 0 bet
	else if (decision == 'F') {
		return 0;
	}

	//if all else fails, send back a 0 bet
	return 0;
}