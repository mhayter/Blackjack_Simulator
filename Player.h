
#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include "Deck.h"

#include "Dealer.h"

class Player {
public:
    Player():  nWagers(0), handPlace(0), money(1000), wager(STANDARD_WAGER) {
    }
    virtual ~Player() {}

	virtual void play(Deck &deck, const Card& upCard)=0;
	void lose() {
        money-= hands[handPlace].getWager();
    }
	void win(bool blackjackWin=false) {
        money+= hands[handPlace].getWager()+blackjackWin*hands[handPlace].getWager()*0.5;
    }
	virtual void tie() {}

	bool hasBlackJack() {
		return hands[handPlace].isBlackJack();
	}
	bool bust() {
		return hands[handPlace].bust();
	}
	int getHandValue() {
		return hands[handPlace].getHandValue();
	}
	void clear() {
		hands.clear();
		handPlace = 0;
	}
	void addCard(const Card &card) {
		////cerr << "Add Card Player " << endl;
		//if (hands.size() == 0) hands.push_back(Hand());
		hands[handPlace].addCard(card);
	}
	Hand getHand() {
		return hands[handPlace];
	}
	void addHand(const Hand &hand) {
		hands.push_back(hand);
	}
	void evaluateHands(Dealer *dealer, Deck &deck) {
		int nTimes = 4;
		//cerr << "Before evaluateHands " << endl;
		//cerr << "handPlace " << handPlace << endl;
        //cout << "**********player Hand " << getHand() << " " << getHandValue() << endl;
        
        if (hasBlackJack() && !dealer->hasBlackJack()) {//pay player 1.5x
        	nWagers++;
            win(true);
            //cout << "True BJ!!!" << endl;
            dealer->lose(hands[handPlace].getWager(), true);
        }
        else if (hasBlackJack() && dealer->hasBlackJack()) {//push
            //cout << "Push" << endl;
            nWagers++;
            tie();
            dealer->tie();
        }
        else if (dealer->hasBlackJack() && !hasBlackJack()) { // dealer wins
            //cout << "Lose :( dealer BJ" << endl;
            nWagers++;
            dealer->win(hands[handPlace].getWager());
            lose();
            
        } else {
            //cout << "Before play with dealer " << dealer->getUpCard() << endl;
           //while I don't bust or stand ask for hit
           play(deck, dealer->getUpCard());
        
            //cout << "**After play player Hand " << getHand() << " " << getHandValue() << endl;

			while (handPlace < (int) hands.size() && nTimes--) {
                //if I didn't bust and he did I win
                if (bust()) {//bust
                    ////cout << "Player bust" << endl;
                    dealer->win(hands[handPlace].getWager());
                    lose();

                } else {
                    dealer->play(deck, dealer->getUpCard()); // doesn't need upCard (eliminate?)

                    //cout << "**Dealer Hand " << dealer->getHand() << endl;

                    if (dealer->bust()) {// bust player wins
                        //cout << "Dealer Bust" << endl;
                        win();
                        dealer->lose(hands[handPlace].getWager());
                    } else if (getHandValue() > dealer->getHandValue()) {
                        //cout << "Player Win!" << endl;
                        win();
                        dealer->lose(hands[handPlace].getWager());
                    } else if (getHandValue() < dealer->getHandValue()) {
                        //cout << "Player Lose :(" << endl;
                        dealer->win(hands[handPlace].getWager());
                        lose();
                    } else { // tie
                        //cout << "Push ---" << endl;
                        dealer->tie();
                        tie();
                    }
                }
                (handPlace)++;
            }
        }
        //cerr << dealer->money << " " << money << endl;
	}
	int nWagers;
    vector<Hand> hands;
    int handPlace;

	double money;
	int wager;
	const static int STANDARD_WAGER = 25;
};
#endif