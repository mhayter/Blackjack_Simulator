#ifndef ADVANCED_PLAYER_H
#define ADVANCED_PLAYER_H

#include "Player.h" 
#include "Dealer.h"

class AdvancedPlayer : public Player {
public:
	AdvancedPlayer() {}
	virtual ~AdvancedPlayer() {}
	virtual void play(Deck &deck, const Card &upCard) override {
		//100% coverage on double down
		handPlace = 0;

		while (handPlace < (int)hands.size()) {
			nWagers++;
			while (split(deck,upCard, hands[handPlace]));
			//cerr << "Done splitting" << endl;
			if (doubleDown(deck,upCard, hands[handPlace])) {
				//cout << "Doubled Down!" << endl;
				nWagers++;
			} else {
				//keep hitting until stand
				////cerr << "hitting?" << endl;
				 while (hit(deck,upCard, hands[handPlace]));
			}
			handPlace++;
		}
		handPlace = 0;
		//working logic
		//cerr << "hands.size " << hands.size() << endl;
	}
	
	virtual void tie() {}
private:

	////////// Split /////////////////////////
	bool split(Deck &deck, const Card &upCard, Hand &myHand) {
		if (myHand.isSplittable()) {
			//logic for splitting
			if (shouldSplit(upCard,myHand)) { // need money
				doSplit(deck, upCard, myHand);
				return true;
			}
		}
		return false;
	}
	bool shouldSplit(const Card &upCard, Hand &myHand) {
		//return false;
		if (myHand.getHandValue() == 10) return false;
		if (myHand.getHandValue() == 20) return false; // stand
		if (upCard.getValue() <= 7) {
			//
			if (myHand.getHandValue() == 8) { // hit
				if (myHand.getHandValue() >=5 && myHand.getHandValue() <=6) {//hit
					return true;
				} else 
					return false;
			} 

			if (myHand.getHandValue() == 12 && upCard.getValue() == 7) { // hit
				return false;
			}
			if (myHand.getHandValue() == 18 && upCard.getValue() == 7) { // stand
				return false;
			}
			return true; //split
		} else {
			if (myHand.getHandValue() >=4 && myHand.getHandValue() <= 14) {
				return false; //hit
			} else {

				if (upCard.getValue() >= 10) { //stand
					return false;
				} else 
					return true;
			}
		}
		
	}
	void doSplit (Deck &deck, const Card &upCard, Hand &myHand) {
		//cout << "Splitting!" <<endl;

		Hand nextHand = myHand.doSplit(deck);
		hands.push_back(nextHand);
	}

	////////////// Double Down ///////////////////////////
	bool doubleDown(Deck &deck, const Card &upCard, Hand &myHand) {
		if (shouldDoubleDown(upCard,myHand)) {
			myHand.doDoubleDown(deck);
			return true;
		}
		return false;
	}
	bool shouldDoubleDown(const Card &upCard, const Hand &myHand) {
		//cerr << "myHand " << myHand << " up " << upCard << " value " << myHand.getHandValue() << endl;
		//return false;
		if (myHand.getHandValue() == 11 ||
				(myHand.getHandValue() == 10 && upCard.getValue() <= 9) ||
				(myHand.getHandValue() == 9  && upCard.getValue() >=3 && upCard.getValue() <=6)) {
			return true;
		}
		if (myHand.isSoft()) {
			if (upCard.getValue()>=5 && upCard.getValue() <=6 && 
				myHand.getHandValue()>=13 && myHand.getHandValue() <=18) {
				return true;		
			}
			if (upCard.getValue() == 4 && 
				myHand.getHandValue()>=15 && myHand.getHandValue() <=18) {
				return true;
			} 
			if(upCard.getValue() == 3 &&
				myHand.getHandValue()>=17 && myHand.getHandValue() <=18){
				return true;
			} 
			if (upCard.getValue() == 2 &&
				myHand.getHandValue() == 18) {
				return true;
			}
			if (upCard.getValue() == 6 &&
				myHand.getHandValue() == 19) {
				return true;
			}
		}
		return false;
	}


	//////////////// HIT //////////////////////////////
	bool hit(Deck &deck, const Card &upCard, Hand &myHand) {
		if (shouldHit(upCard,myHand)) {
			////cerr << "Actual hit" << endl;
			myHand.doHit(deck);
			return true;
		}
		////cerr << "Not hitting" << endl;
		return false;
	}
	double shouldHit(const Card &upCard, const Hand &myHand) {
		if (myHand.isSoft()) {
			if (myHand.getHandValue() >= 19) return false;
			if (myHand.getHandValue() >= 18) {
				if (upCard.getValue() <=6){ 
					cerr << "should Have doubled?" << endl;
					cerr << myHand << " value " << myHand.getHandValue() << " up " << upCard << endl;
				}
				if (upCard.getValue() >= 7 && upCard.getValue()<=8) {
					return false; //stand
				}
			}

		} else {
			if (upCard.getValue() >=2 && upCard.getValue() <= 6) {
				if (myHand.getHandValue() >= 12 && myHand.getHandValue() <=16) {//stand
					if (myHand.getHandValue() >= 2 || myHand.getHandValue() <=3)
						return true;
					else
						return false;
				}
			}
			if (myHand.getHandValue() >= 17) return false; // stand
		}
		return true;

	}
};

#endif