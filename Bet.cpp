#include "Bet.h"

Bet::Bet(int bettingPlayer, int bettingAmount){
	player = bettingPlayer;
	amount = bettingAmount;
}

int Bet::getAmount(){
	return amount;
}

int Bet::getPlayer(){
	return player;
}