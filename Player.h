#include "Hand.h"
#include "BetHistory.h"

class Player{
	public:	
		virtual int getBet(Hand, BetHistory, int, bool, int) = 0;
		void setID(int);
		int getID();
		void setHand(Hand);
		Hand getHand();
		void setChips(int);
		int getChips();

	private:
		int id;
		Hand hand;
		int chips;
};