/* CSCI 261A: Final Project: class and function implementation. 
        Author: Lexi Drgac, Gazi Morshed. 
*/

#include "player.h"
#include<vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


player::player(){ //default constructor. 
    _hand;
    _score = 0;
    
}

player :: player (vector<card> hand, int score) { //parametarized constructor. 
        _hand = hand;
        _score = score;
    } 
void player::setHand(vector<card> copy1hand) {  //setter
    _hand = copy1hand;
}
vector<card> player::getHand() const{ //getter
    return _hand;
}
void  player::setScore (int score) { //setter
        _score = score;
    }
int player::getScore ()const { //getter
        return _score;
    }
int player::checkForPair (int score, int n) { // this function recieves the score from the main function and a variable to help with the 
    // recursion and returns the scores calculated by the function. 
    bool breakOUT =false;
    if ( n == 3) {   //base case. 
        // there can be at most three pairs in a hand of 7 cards. 
        return score;
    }
    else {   // goes through the cards in the hand one by one and compare with each other to find if there's any pair. 
        for (unsigned int i=0; i<this->_hand.size(); i++) { 
            for (unsigned int j=0; j< this->_hand.size(); j++) {
                if (this->_hand.at(i).rank == this->_hand.at(j).rank) { //for a pair to happen and increment the score, the rank of a card has to be same, regardless of the suit. 
                    if (i == j) { // ignoring when the card is ignored with itself. 
                       continue;
                    }
                    else {
                        this->_hand.erase(this->_hand.begin()+ i);  //otherwise the cards are erased from both places of the deck. 
                        this->_hand.erase(this->_hand.begin()+ (j-1));
                        score++;
                        breakOUT =true;
                        break;
                    }
                }
                else {
                    continue;
                }
            }
            if(breakOUT == true) {
                break;
            }
        }    
    }
    n++;
    return checkForPair(score, n); // recursive part, executing if a pair is not found yet. 
}
bool player::askForCard (player &that, int choosenIndex) { // player asks for card and function checks if other player has it in their hand.
    vector<card> tempDeck = that.getHand(); // crreating a temporary deck to push into vector
    cout<<endl;
    for (unsigned int j=0; j< that.getHand().size(); j++) {  // for every element is the target's hand
        if (this->_hand.at(choosenIndex-1).rank == that.getHand().at(j).rank) { // if callee's card rank equals the other player's card rank at index 
            this->_hand.push_back(that.getHand().at(j)); // then put into callee's hand
            tempDeck.erase(tempDeck.begin() + j); // erase from target's hand
            that.setHand(tempDeck); // setting callee's new hand
            cout<<"Found Match, here is my card :-( " << endl;
          
            return true; // return true
            break; // break from for loop
        }
    }
    return false; // if no matches reutrn false
}

void player :: goFish ( vector<card> &deck) { // draws a card from back of deck and erases from deck
    cout<<"I don't have that card, go fish."<<endl; // telling other player to go fish
    card tempCard = deck.back(); // temporary card to push into hand
    deck.pop_back(); // deleting drawn card from the deck
    this->_hand.push_back(tempCard); // pushing temporary card into callee's hand
} 
bool player :: lowDeck() { // if the callee has a low deck
     if(this->_hand.size() < 1 ) { // if callee's hand gets below 1
         return true; //return true
     }
     else {
         return false; // if callee's hand is above 1 return false
     }
 }


vector<card> makeDeck() {
vector<card> copydeck;  // didn't declare the vector with the 52 elements as I wanted to check to see if my card assignment was correct or not. 
card temporaryCard;
for( unsigned int i=0; i<4; i++) {    // this is for the suit. 
        if( i==0 ){   // first cards are clubs
            temporaryCard.suit = "clubs";  // store the suit on a temporary card
            }
            else if (i==1) { // then we have dimaonds card
                temporaryCard.suit = "diamond";
            }
            else if (i==2) {  //then all hearts card
                temporaryCard.suit = "hearts";
            }
            else if (i==3) { // and the rest are spades,, 13 from each suit, 52 total. 
                temporaryCard.suit = "spades";
            }
        for (unsigned int j=1; j<14; j++) {  // this is for the rank on every suit. 
            temporaryCard.rank =j;  // store the rank on a temporary card
            copydeck.push_back(temporaryCard);  // now the temporary card has the appropiate suit and rank and it will be used to construct the deck vector with 52 cards. 
        }
    }
    return copydeck;
}


void printCard(vector<card> copy1Deck) {  //this function has been used to test and print out the whole deck of cards, at times they were arranged, at times they were shuffled. Although it is not being used in the main function currently. 
     for (unsigned int i=0; i<copy1Deck.size(); i++) { // go through each and every card in the deck. 
            if (copy1Deck.at(i).rank==1) { // at postion 1, the card has rank of 1, which is called Ace. 
                cout<<i+1<<". Ace of "<<copy1Deck.at(i).suit<<endl;
            }
            else if (copy1Deck.at(i).rank==11) { // at position 11 ,the card name is Jack. 
                cout<<i+1<<". Jack of "<<copy1Deck.at(i).suit<<endl;
            }
            else if (copy1Deck.at(i).rank==12) { // at position 12 ,the card name is Queen. 
                cout<<i+1<<". Queen of "<<copy1Deck.at(i).suit<<endl;
            }
            else if (copy1Deck.at(i).rank==13) { // at position 13 ,the card name is King. 
                cout<<i+1<<". King of "<<copy1Deck.at(i).suit<<endl;
            }
            else { //for all the other rank, print them out as their rank is. 
            cout<<i+1<<". "<<copy1Deck.at(i).rank << " of "<<copy1Deck.at(i).suit<<endl;
            }
        }
 }
 
  void shuffleDeck(vector<card> &copy2Deck) {  // this function shuffles the cards around randomly. while it changes the deck here, it changes it in the main function. hence the &
    int fromCard, toCard; 
    vector<card>tempCard(1); //a temporary vector has created to store a card,while swapping them with another one. 
    srand(time(0));
    for (unsigned int i = 0; i<100; i++) { //it will swap 100 times
    fromCard= rand() % 52; //52 postions from index 0 to 51. 
    toCard= rand() % 52;
    tempCard.at(0) = copy2Deck.at(fromCard); //put from a random postion to the temporay vector
    copy2Deck.at(fromCard) = copy2Deck.at(toCard); // from another random postion to the previous ramdom. 
    copy2Deck.at(toCard) = tempCard.at(0);  // temporary to second random. 
    }
 }
 
 vector<card> makeInitialHand(vector<card> &deck){ // making intial hands for callee
    vector<card> tempHand; // temp hand 
    card tempCard; // tempcard
    for (unsigned int i =0; i < 7; ++i){ // a hand gets composed of 7 cards
        tempCard.rank = deck.back().rank; // drawing from deck and setting rank and suit
        tempCard.suit = deck.back().suit; 
        tempHand.push_back(tempCard); // pushing temp card into initial hand
        
        deck.pop_back(); // removing delt card from deck
    }
    return tempHand; // returning intial hand to callee
}

void printCurrentCard ( card currDealCard1) { //this functions prints out only a single card, the card in play to be specific. 
    if (currDealCard1.rank==1) {  // at postion 1, the card has rank of 1, which is called Ace.
        cout<<"Ace of "<<currDealCard1.suit<<endl;
    }
    else if (currDealCard1.rank==11) {   // at position 11 ,the card name is Jack.
        cout<<"Jack of "<<currDealCard1.suit<<endl;
    }
    else if (currDealCard1.rank==12) {   // at position 12 ,the card name is Queen.
        cout<<"Queen of "<<currDealCard1.suit<<endl;
    } 
    else if (currDealCard1.rank==13) {  // at position 13 ,the card name is King.
        cout<<"King of "<<currDealCard1.suit<<endl;
    }
    else {   //for all the other rank, print them out as their rank is.
        cout<<currDealCard1.rank << " of "<<currDealCard1.suit<<endl;
    }
}