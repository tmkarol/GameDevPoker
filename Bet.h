#pragma once
class Bet{
	public:
		Bet(int, int);
		int getPlayer();
		int getAmount();

	private:
		int player;
		int amount;
};