#include "AlphaPlayer.h"
#include <iostream>

using namespace std;

AlphaPlayer::AlphaPlayer() {
}

int AlphaPlayer::getBet(Hand opponent, BetHistory bh, int bet2player, int pot, bool lastRound, bool canRaise) {
	int delta, potFactor;
	delta = hand.evaluateHand() - opponent.evaluateHand(); //this value comes into the decision making for how much to bet

	//decision making in this section is done according to the Alpha Type AI Rules in the project description
	if (!lastRound) {
		if (bh.getCount() == 0) {
			if (delta > 10 && canRaise) {
				chips -= 10;
				cout << "Alpha raises 10!" << endl << endl;
				return 10;
			}
			else if (delta > 5 && canRaise) {
				chips -= 5;
				cout << "Alpha raises 5!" << endl << endl;
				return 5;
			}
			else if (delta > 0 && canRaise) {
				chips -= 1;
				cout << "Alpha raises 1!" << endl << endl;
				return 1;
			}
			else {
				cout << "Alpha checks!" << endl << endl;
				return 0;
			}
		}
		else {
			potFactor = pot / 10;
			if (bet2player == 0) {
				if (delta > (5 - potFactor) && canRaise) {
					chips -= 10;
					cout << "Alpha raises 10!" << endl << endl;
					return 10;
				}
				else if (delta > (0 - potFactor) && canRaise) {
					chips -= 1;
					cout << "Alpha raises 1!" << endl << endl;
					return 1;
				}
				else {
					cout << "Alpha calls!" << endl << endl;
					return 0;
				}
			}
			else if (bet2player < (1 + potFactor * 2)) {
				if (delta > (8 - potFactor) && canRaise) {
					chips -= bet2player + 10;
					cout << "Alpha raises 10!" << endl << endl;
					return bet2player + 10;
				}
				else if (delta > ((-2) - potFactor) && canRaise) {
					chips -= bet2player + 1;
					cout << "Alpha raises 1!" << endl << endl;
					return bet2player + 1;
				}
				else if (delta > ((-4) - potFactor)) {
					chips -= bet2player;
					cout << "Alpha calls!" << endl << endl;
					return bet2player;
				}
				else {
					cout << "Alpha folds!" << endl << endl;
					return 0;
				}
			}
			else {
				if (delta > (10 - potFactor) && canRaise) {
					chips -= bet2player + 10;
					cout << "Alpha raises 10!" << endl << endl;
					return bet2player + 10;
				}
				else if (delta > (0 - potFactor) && canRaise) {
					chips -= bet2player + 1;
					cout << "Alpha raises 1!" << endl << endl;
					return bet2player + 1;
				}
				else if (delta > ((-2) - potFactor)) {
					chips -= bet2player;
					cout << "Alpha calls!" << endl << endl;
					return bet2player;
				}
				else {
					cout << "Alpha folds!" << endl << endl;
					return 0;
				}
			}
		}
	}
	else {
		if (bh.getCount() == 0) {
			if (delta > 10 && canRaise) {
				chips -= 10;
				cout << "Alpha raises 10!" << endl << endl;
				return 10;
			}
			else if (delta > 5 && canRaise) {
				chips -= 5;
				cout << "Alpha raises 5!" << endl << endl;
				return 5;
			}
			else {
				cout << "Alpha folds!" << endl << endl;
				return 0;
			}
		}
		potFactor = pot / 10;
		if (bet2player == 0) {
			if (delta > (10 - potFactor) && canRaise) {
				cout << "Alpha raises 10!" << endl << endl;
				chips -= 10;
				return 10;
			}
			else {
				cout << "Alpha calls!" << endl << endl;
				return 0;
			}
		}
		else if (bet2player < (1 + potFactor * 2)) {
			if (delta > (6 - potFactor) && canRaise) {
				cout << "Alpha raises 10!" << endl << endl;
				chips -= bet2player + 10;
				return bet2player + 10;
			}
			else if (delta > 2) {
				cout << "Alpha calls!" << endl << endl;
				chips -= bet2player;
				return bet2player;
			}
			else {
				cout << "Alpha folds!" << endl << endl;
				return 0;
			}
		}
		else {
			if (delta > (8 - potFactor) && canRaise) {
				cout << "Alpha raises 10!" << endl << endl;
				chips -= bet2player + 10;
				return bet2player + 10;
			}
			else if (delta > 4) {
				cout << "Alpha calls!" << endl << endl;
				chips -= bet2player;
				return bet2player;
			}
			else {
				cout << "Alpha folds!" << endl << endl;
				return 0;
			}
		}
	}
}