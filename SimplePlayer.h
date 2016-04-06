#ifndef SIMPLE_PLAYER_H
#define SIMPLE_PLAYER_H

#include "Player.h" 

class SimplePlayer : public Player {
public:
	SimplePlayer() {}
	virtual ~SimplePlayer() {}
	virtual void play(Deck &deck, const Card &upCard) override {
		//Hit
        while (hands[handPlace].getHandValue()<=14) { // -0.0502
            hands[handPlace].addCard(deck.deal());
        }
	}
	virtual void tie() {}
private:
};

#endif