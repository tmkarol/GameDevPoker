#include "BetaPlayer.h"
#include <iostream>
#include <ctime>
using namespace std;

BetaPlayer::BetaPlayer() {
	srand(time(0));
}


//Helper function that provides some fuzziness to the logic
float muddle(float baseline, float variance){
	float randf_normal = -1.0 + (rand() % 1 + rand() % 1 + rand() % 1 ) / 1.5;
	return (baseline - variance) + variance * randf_normal;
}

int BetaPlayer::getBet(Hand opponent, BetHistory bh, int bet2player, int pot, bool lastRound, bool canRaise, bool reportFlag) {
	int delta;
	float potFactor;
	delta = hand.evaluateHand() - opponent.evaluateHand(); //this value comes into the decision making for how much to bet

	//decision making in this section is done according to the Alpha Type AI Rules in the project description
	if (!lastRound) {
		if (bh.getCount() == 0) {
			if (delta > 10 && canRaise) {
				chips -= 10;
				if (reportFlag) {
					cout << "Beta raises 10!" << endl << endl;
				}

				return 10;
			}
			else if (delta > 5 && canRaise) {
				chips -= 8;
				if (reportFlag) {
					cout << "Beta raises 8!" << endl << endl;
				}
				return 8;
			}
			else if (delta > 0 && canRaise) {
				chips -= 1;
				if (reportFlag) {
					cout << "Beta raises 1!" << endl << endl;
				}
				return 1;
			}
			else {
				if (reportFlag) {
					cout << "Beta checks!" << endl << endl;
				}
				return 0;
			}
		}
		else {
			//pick a pot factor that is seemingly random
			potFactor = muddle((float) pot, 20) ;
			if (bet2player == 0) {
				if (delta > (5 - potFactor) && canRaise) {
					chips -= 10;
					if (reportFlag) {
						cout << "Beta raises 10!" << endl << endl;
					}
					return 10;
				}
				else if (delta > (0 - potFactor) && canRaise) {
					chips -= 3;
					if (reportFlag) {
						cout << "Beta raises 3!" << endl << endl;
					}
					return 3;
				}
				else {
					if (reportFlag) {
						cout << "Beta calls!" << endl << endl;
					}
					return 0;
				}
			}
			else if (bet2player < (1 + potFactor * 2)) {
				if (delta > (8 - potFactor) && canRaise) {
					chips -= bet2player + 10;
					if (reportFlag) {
						cout << "Beta raises 10!" << endl << endl;
					}
					return bet2player + 10;
				}
				else if (delta > ((-2) - potFactor) && canRaise) {
					chips -= bet2player + 1;
					if (reportFlag) {
						cout << "Beta raises 1!" << endl << endl;
					}
					return bet2player + 1;
				}
				else if (delta > ((-4) - potFactor)) {
					chips -= bet2player;
					if (reportFlag) {
						cout << "Beta calls!" << endl << endl;
					}
					return bet2player;
				}
				else {
					if (reportFlag) {
						cout << "Beta folds!" << endl << endl;
					}
					return 0;
				}
			}
			else {
				if (delta > (10 - potFactor) && canRaise) {
					chips -= bet2player + 10;
					if (reportFlag) {
						cout << "Beta raises 10!" << endl << endl;
					}
					return bet2player + 10;
				}
				else if (delta > (0 - potFactor) && canRaise) {
					chips -= bet2player + 1;
					if (reportFlag) {
						cout << "Beta raises 1!" << endl << endl;
					}
					return bet2player + 1;
				}
				else if (delta > ((-2) - potFactor)) {
					chips -= bet2player;
					if (reportFlag) {
						cout << "Beta calls!" << endl << endl;
					}
					return bet2player;
				}
				else {
					if (reportFlag) {
						cout << "Beta folds!" << endl << endl;
					}
					return 0;
				}
			}
		}
	}
	else {
		if (bh.getCount() == 0) {
			if (delta > 10 && canRaise) {
				chips -= 10;
				if (reportFlag) {
					cout << "Beta raises 10!" << endl << endl;
				}
				return 10;
			}
			else if (delta > 5 && canRaise) {
				chips -= 8;
				if (reportFlag) {
					cout << "Beta raises 8!" << endl << endl;
				}
				return 8;
			}
			else {
				if (reportFlag) {
					cout << "Beta folds!" << endl << endl;
				}
				return 0;
			}
		}
		potFactor = pot / 10;
		if (bet2player == 0) {
			if (delta > (10 - potFactor) && canRaise) {
				if (reportFlag) {
					cout << "Beta raises 10!" << endl << endl;
				}
				chips -= 10;
				return 10;
			}
			else {
				if (reportFlag) {
					cout << "Beta calls!" << endl << endl;
				}
				return 0;
			}
		}
		else if (bet2player < (1 + potFactor * 2)) {
			if (delta > (6 - potFactor) && canRaise) {
				if (reportFlag) {
					cout << "Beta raises 10!" << endl << endl;
				}
				chips -= bet2player + 10;
				return bet2player + 10;
			}
			else if (delta > 2) {
				if (reportFlag) {
					cout << "Beta calls!" << endl << endl;
				}
				chips -= bet2player;
				return bet2player;
			}
			else {
				if (reportFlag) {
					cout << "Beta folds!" << endl << endl;
				}
				return 0;
			}
		}
		else {
			if (delta > (8 - potFactor) && canRaise) {
				if (reportFlag) {
					cout << "Beta raises 10!" << endl << endl;
				}
				chips -= bet2player + 10;
				return bet2player + 10;
			}
			else if (delta > 4) {
				if (reportFlag) {
					cout << "Beta calls!" << endl << endl;
				}
				chips -= bet2player;
				return bet2player;
			}
			else {
				if (reportFlag) {
					cout << "Beta folds!" << endl << endl;
				}
				return 0;
			}
		}
	}
}



