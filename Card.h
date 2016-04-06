
#ifndef CARD_H
#define CARD_H
#include <iostream>

class Card {
public:
    Card() = delete;
	Card (char value,char suit) {
		this->value = value;
		this->suit = suit;
	}
    Card (const char *combo) {
        value = combo[0];
        suit = combo[1];
    }
    int getValue() const {
        switch (value) {
            case 'A':
                return 11;
            case 'K':
            case 'Q':
            case 'J':
                return 10;
            case 'T':
                return 10;
            default:
                return (int)(value-'0');
        }
    }
    friend std::ostream& operator << (std::ostream &os, const Card &card) {
        os << card.value << card.suit;
        return os;
    }
	char value;
	char suit;
};
#endif