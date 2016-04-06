#ifndef HAND_H
#define HAND_H

#include <vector>
#include <iostream>
#include "Card.h"
#include "Deck.h"
using std::vector;
using std::endl;
using std::cerr;


class Hand {
public:
    Hand() = delete;
    Hand(int wager){
        this->wager = wager;
        //cerr << "Hand ctor" << endl;
        //cards.push_back(Card("KS"));
    }
    ~Hand(){cards.clear();}

    int getHandValue() const {
        int value =0;
        //bool Has ace
        for (int i=0;i<(int)cards.size();i++) {
            value += cards[i].getValue();
        }
        int nAces = getAceCount();
        if (nAces > 1) {
            value-=(nAces-1)*10;
        }
        if (value > 21 && nAces){
            value -= 10;
        }
        return value;
    }
    void addCard(const Card &card) {
        cards.push_back(card);
    }
    bool bust() const {
        return getHandValue() > 21;
    }
    Card firstCard() { // only for Dealer
        return cards[0];
    }
    int getAceCount() const {
        int cnt = 0;
        for(int i=0;i<(int)cards.size();i++) {
            if (cards[i].value == 'A') {
                cnt++;
            }
        }
        return cnt;
    }
    bool isSoft() const {
        return getAceCount() == 1 && cards.size() == 2;
    }
    bool isBlackJack() const { //splitting may fuck up
        if (cards.size() == 2) {
            return (getHandValue() == 21);
        }
        return false;
    }
    bool isSplittable() {
        return cards.size() == 2 && (cards[0].value == cards[1].value);
    }
    ///
    Card getCard() {
        return cards[1];
    }
    void setCard(const Card &card) {
        cards[1] = card;
    }
    ///
    void clear() {
        this->cards.clear();
    }
    //////////////////Actions
    Hand doSplit(Deck &deck) {

        Hand nextHand(this->wager);
        nextHand.addCard(getCard()); // change?
        
        nextHand.addCard(deck.deal());
        setCard(deck.deal());
        return nextHand;
        
    }
    void doDoubleDown(Deck &deck){
        this->addCard(deck.deal());
        this->wager *= 2;
    }
    void doHit(Deck &deck) {
        this->addCard(deck.deal());
    }
    friend std::ostream& operator<<(std::ostream &os, const Hand &hand) {
        for(int i=0;i<(int)hand.cards.size();i++) {
            os << hand.cards[i] << " ";
        }
        return os;
    }
    int getWager() {
        return wager;
    }
private:
    int wager;
    vector<Card> cards;
};


#endif