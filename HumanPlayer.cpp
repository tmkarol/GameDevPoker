#include "HumanPlayer.h"
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer(){
	type = HUMAN;
}

int HumanPlayer::getBet(Hand opponent, BetHistory bh, int bet2player, int pot, bool lastRound, bool canRaise){
	char decision;
	int raise;
	cout << "Here are your cards:" << endl;
	hand.print();
	cout << endl << "Here is your opponents visible cards:" << endl;
	opponent.print();
	cout << endl << "The current raise is: " << bet2player << endl;
	cout << "the pot contains: " << pot << " chips" << endl;
	cout << "You have " << chips << " chips" << endl;
	if(!canRaise){
		cout << "You can't raise anymore! Would you like to call or fold? (Enter C or F) ";
		cin >> decision;
		cout << endl;
		if(decision == 'Q'){
			return -1;
		}
		while(decision != 'C' && decision != 'F'){
			cout << "Must pick a valid option! (Enter C or F) ";
			cin >> decision;
			cout << endl;
			if(decision == 'Q'){
			return -1;
		}
		}
	}
	else if(bet2player == 0){
		cout << "Would you like to raise or call? (Enter R or C) ";
		cin >> decision;
		cout << endl;
		if(decision == 'Q'){
			return -1;
		}
		while(decision != 'C' && decision != 'R'){
			cout << "Must pick a valid option! (Enter R or C) ";
			cin >> decision;
			cout << endl;
			if(decision == 'Q'){
			return -1;
		}
		}
	}
	else{
		cout << "Would you like to raise, call or fold? (Enter R, C or F) ";
		cin >> decision;
		cout << endl;
		if(decision == 'Q'){
			return -1;
		}
		while(decision != 'C' && decision != 'F' && decision != 'R'){
			cout << "Must pick a valid option! (Enter R, C or F) ";
			cin >> decision;
			cout << endl;
			if(decision == 'Q'){
			return -1;
		}
		}
	}
	if(decision == 'R'){
		cout << "How much would you like to raise? (Max raise is 10) ";
		cin >> raise;
		cout << endl;
		while(raise > 10 || raise < 1){
			cout << "Must raise amount between 1 and 10 ";
			cin >> raise;
			cout << endl;
		}
		chips -= raise;
		return raise;
	}
	else if(decision == 'C'){
		chips -= bet2player;
		return bet2player;
	}
	else if(decision == 'F'){
		return 0;
	}
	return 0;

}