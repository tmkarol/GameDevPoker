#include <iostream>
#include <string>
#include "Game.h"

using namespace std;

int main(){
	Game game;
	game.playGame(HUMAN, ALPHA, 1000, 1000, true);
	return 0;
}