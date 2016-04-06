#include <iostream>
#include <type_traits>
#include <cassert>

#include "Hand.h"
#include "Card.h"
using namespace std;

const bool equals(Hand &hand,int value) {
	cerr << hand.getHandValue() << endl;
	return (hand.getHandValue() == value);
}

int main(){
	Card card1("AS");
	cout << card1 << endl;

	Hand hand1;
	hand1.addCard(Card("AS"));
	hand1.addCard(Card("TC"));


	assert(equals(hand1,21));
	hand1.addCard(Card("AD"));


	assert(equals(hand1,12));

	Hand hand2;
	hand2.addCard(Card("TC"));
	hand2.addCard(Card("QD"));

	assert(equals(hand2,20));


	Hand hand3;
	hand3.addCard(Card("JC"));
	hand3.addCard(Card("2D"));

	assert(equals(hand3,12));

	hand3.addCard(Card("AD"));
	assert(equals(hand3,13));

	hand3.addCard(Card("KC"));
	assert(equals(hand3,23));
	
	return 0;
}