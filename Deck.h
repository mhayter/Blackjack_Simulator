#ifndef DECK_H
#define DECK_H

#include <vector>
#include <iostream>
#include "Card.h"
#include <algorithm>
#include <iterator>
using std::cerr;
using std::vector;

class Deck {
public: 
    Deck(): deckPlace(0), DECK_SIZE(STANDARD_DECK_SIZE) {
        createDeck();
    }
    Deck(int num): deckPlace(0), DECK_SIZE(num * STANDARD_DECK_SIZE){
        createDeck();
    }
    void shuffle() {
        std::random_shuffle(begin(deck),end(deck));
    }
    Card deal() {
        if (deckPlace < DECK_SIZE)
            return deck[deckPlace++];
        else {
            cerr << "deck out of place Exception";
            return Card("FU");
        }
    }
    void reset() {
        deckPlace = 0;
        shuffle();
    }
private:
    void createDeck() {
        for(int i=0;i<DECK_SIZE;i++) {
            deck.push_back(Card(VALUES[i%13],SUITS[i%4]));
        }
        shuffle();
    }
    int deckPlace;
    int DECK_SIZE; //cant be const kills assignment operator
    static constexpr int STANDARD_DECK_SIZE = 52;
    static constexpr const char* VALUES = "23456789TJQKA";
    static constexpr const char* SUITS = "CSDH";
    vector<Card> deck;
};
#endif