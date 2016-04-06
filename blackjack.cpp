#include <iostream>
#include <vector>
using namespace std;

#include "Hand.h"
#include "Card.h"
#include "Deck.h"

#include "Dealer.h"
#include "SimplePlayer.h"
#include "AdvancedPlayer.h"


// 1 deck should be +0.00122 +0.00107//hand
// 4 deck should be -0.00325 -0.00286//hand
class BlackJack{
public:
    BlackJack(int nDecks=4, int nPlayers=2) : 
        nDecks(nDecks), deck(nDecks)
    {
        player = new AdvancedPlayer();
        dealer = new Dealer();
    }
    BlackJack(Deck &deck) :
        deck(deck) 
    {
        player = new AdvancedPlayer();
        dealer = new Dealer();
    }
    ~BlackJack() {
        delete player;
        delete dealer;
    }
    double getResult(int nBets = 100, int wager=25) {
        while (nBets-- > 0 && player->money > 0) {
            //cout << "New Hand " << player->money << endl;
            //int z; cin >> z;
            if (player->money <= 0) {
                cout << "You Lost" << endl;
                break;
            }
            reset();
        	//deal cards 
            //cout << "Before dealHands" << endl;
        	dealHands(wager);
            //cout << "dealHands" << endl;
            // for each of the hands evaluate
            player->evaluateHands(dealer,deck);
            
            
        }
        //cerr << "Wagered " << player->nWagers * 25<< endl; 
        return player->money;
    }
    double getWagered() {
        return player->nWagers * 25;
    }
private:
    void reset() {
        deck.reset();
        //deck = Deck(nDecks);
        dealer->clear();
        player->clear();
    }
    void dealHands(int wager) {
        Hand dealerHand(wager); // dealer isn't a player truly
        dealerHand.addCard(deck.deal());
        dealerHand.addCard(deck.deal());

        dealer->addHand(dealerHand);

        Hand playerHand (wager);
        playerHand.addCard(deck.deal());
        playerHand.addCard(deck.deal());

        player->addHand(playerHand);
    }
    int nDecks;

    Dealer *dealer;
    Deck deck;
    Player *player;
};

int main(int argc, char *argv[]) {
   int nSims = 10;

   int nBets = 10; 

   if (argc == 2) {
        nSims = atoi(argv[1]);
   }
   vector<double> results;
   Deck deck(4);
   double totalWagered = 0;
   for (int i=0;i<nSims;i++) {
        //BlackJack bj(4);
        BlackJack bj(deck); //only construct the deck once? 0.8s on 4decks proper rest 10000 
        results.push_back(bj.getResult(nBets));
        totalWagered += bj.getWagered();
        //cerr << (results[i]-1000)/(25*nBets) << endl;
        //cerr << "******* Result " << results[i] << endl;
   }

   //total wagered for eack bet *nBets
   cerr << "Overall \n";
   double tot = 0;
   for(int i=0;i<nSims;i++) {
        tot+=results[i]-1000;
   }
   cerr << "Average loss " << tot / nSims << endl;
   cerr << "Return on wager " << tot / (totalWagered) << endl;
   //bj.play();
   return 0;
}

