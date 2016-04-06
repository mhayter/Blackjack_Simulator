
#ifndef DEALER_H
#define DEALER_H

#include "Deck.h"
#include "Hand.h"

class Dealer {
public:
    Dealer(): money(0), myHand(-1)  { // dummy wager for dealer
    	//cerr << "Dealer ctor" << endl;
    	//cerr << "Deal Hand " << myHand << endl;
    }
    ~Dealer() {

    }
	void play(Deck &deck, const Card &upCard) {
		//Hit Until 17 (hit on soft 17)
		while (myHand.getHandValue() < 17 || (myHand.getHandValue() == 17 && myHand.isSoft())) {
			myHand.addCard(deck.deal());
		}
	}
    void lose(int wager, bool playerBlackJack=false) {
        if (playerBlackJack) money -= 1.5*wager;
        else money-=wager;
    }
    void win(int wager) {
        money+= wager;
    }
    void tie() {}
    void clear() {
        myHand = Hand(-1);
    }
    bool hasBlackJack() {
        return myHand.isBlackJack();
    }
    bool bust() {
        return myHand.bust();
    }
    int getHandValue() {
        return myHand.getHandValue();
    }
    void addCard(const Card &card) {
        //cerr << "Add Card Player " << endl;
        //if (hands.size() == 0) hands.push_back(Hand());
        myHand.addCard(card);
    }
    void addHand(const Hand &hand) {
        myHand = hand;
    }
    Card getUpCard() {
        return myHand.firstCard();
    }
    Hand getHand() {
        return myHand;
    }
    int money;
private:
    Hand myHand;
};
#endif