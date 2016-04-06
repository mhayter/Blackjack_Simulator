#include <iostream>

using namespace std;

#include "AdvancedPlayer.h"
#include "Dealer.h"

int main(){
	AdvancedPlayer player;
	Dealer *dealer = new Dealer();

	Deck deck;

	Hand myHand(25);
	myHand.addCard("AC");
	myHand.addCard("AH");

	player.addHand(myHand);

	Hand dealerHand(-1);
	dealerHand.addCard("6S"); //upcard
	dealerHand.addCard("TC"); 
	dealer->addHand(dealerHand);

	//player.play(deck, upCard); // not quite right 6S in deck ACAS
	player.evaluateHands(dealer, deck);


	return 0;
}