/* CSCI 261A: Final Project: class and function declaration. 
        Author: Lexi Drgac, Gazi Morshed. 
*/

#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


struct card{            //declaring a struct name card which has the rank and suit for each and every card. 
        string suit;   
        int rank;
    };

class player {
    private:
       vector<card> _hand;
       int _score;
       
    public:
       player();
       player(vector<card>, int);
       void setHand(vector<card>);
       void setScore(int);
       vector<card> getHand()const;
       int getScore ()const;
       int checkForPair (int, int);
       bool askForCard(player &that, int );
       void goFish ( vector<card> &deck);
       bool lowDeck();
    
   
};

vector<card> makeDeck(); // making deck

void printCard(vector<card> copy1Deck); // prints cards

void shuffleDeck(vector<card> &copy2Deck); // shuffles deck
  
vector<card> makeInitialHand(vector<card> &deck); // making initial hand

void printCurrentCard ( card currDealCard1);
