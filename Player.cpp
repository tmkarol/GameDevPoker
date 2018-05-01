#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() {
}

void Player::setHand(Hand playerHand) {
	hand = playerHand;
}

Hand Player::getHand() {
	return hand;
}

void Player::setChips(int playerChips) {
	chips = playerChips;
}

int Player::getChips() {
	return chips;
}

