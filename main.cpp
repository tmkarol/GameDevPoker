#include <iostream>
#include <string>
#include "Game.h"

using namespace std;

int main() {
	Game game;
	char decision;
	cout << "Play a game or run Monte Carlo? (Enter 'P' to play game, 'M' to run Monte Carlo, or 'Q' to quit): ";
	cin >> decision;
	if (toupper(decision) == 'Q') {
		return -1;
	}
	while (toupper(decision) != 'P' && toupper(decision) != 'M') {
		cout << "Must pick a valid option! (Enter 'P' or 'M') ";
		cin >> decision;
		cout << endl;
		if (toupper(decision) == 'Q') {
			return -1;
		}
	}
	if (toupper(decision) == 'P') {
		cout << "Which AI would you like to play? (Enter 'A' for Alpha, 'B' for Beta, or 'Q' to quit): ";
		cin >> decision;
		if (toupper(decision) == 'Q') {
			return -1;
		}
		while (toupper(decision) != 'A' && toupper(decision) != 'B') {
			cout << "Must pick a valid option! (Enter 'A' or 'B') ";
			cin >> decision;
			cout << endl;
			if (toupper(decision) == 'Q') {
				return -1;
			}
		}
		if(decision == 'A'){
			game.playGame(HUMAN, ALPHA, 1000, 1000, true);
		}
		else{
			game.playGame(HUMAN, BETA, 1000, 1000, true);
		}
		return 0;
	}
	else {
		game.monteCarlo();
	}
	return 0;
}