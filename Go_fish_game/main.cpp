/* CSCI 261A: Final Project: Go Fishing 
        Author: Lexi Drgac, Gazi Morshed. 
        UserName: lexidrgac, gmdmahbubmorshed
*/
#include <time.h> 
#include<vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include <fstream>
using namespace std;

int main()  {
    vector<card> deck; //making a deck vector
    vector<card> initialHand; //this vector is for the initial player's hands. 
    string again = " ";
    ofstream gamelog; // declare the file to write to.
    gamelog.open("gameinfo.txt");  // open the file
     if (!gamelog ) {  // if the file opening fails, return error. 
         cerr<<"Error opening output file";
         return -1;
     }
     
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
     
     cout << "\nWELCOME TO GO FISHING!! 🐟 \n Instructions: to play, you will be initially shown your delt hand. you hand will automatically be checked fo pairs. Any found pairs will be discarded from your deck "<<endl;
     cout << "and your score will be incremented. You will then be asked to pick a card from your deck to ask the computer for. If the computer has that card, it will be added to your deck." << endl ;
     cout << "If the computer does not have that card, will will go fishing and pull a card from the deck. The computer will follow similar steps. the game ends when there are 5 cards left in" << endl;
     cout << "the deck. Whoever has the most pairs, wins the game." << endl << endl;
     
     cout << "Would you like to play a round? Enter 'Yes' to proceed. Otherwise give us an A and get outta here!" << endl;
     cin >> again;
     
    while  ( (again == "Yes")|| (again == "YES") || (again == "yes") ) {
        int playerScore = 0, computerScore=0;
        int nonsense =0; //this variable helps with the recursion function. 
        unsigned int choosenIndex =0; //index that will player's chooses. 
        deck = makeDeck(); // making the deck. 
        shuffleDeck(deck); //shuffling the deck, 
        initialHand = makeInitialHand(deck); //making a initial hand. 
        player computer(initialHand, computerScore); // initial computer object
        initialHand = makeInitialHand(deck);
        player playerOne(initialHand, playerScore);//initial player object
        cout<<"\nPlayer's initial hand: "<<endl;
        printCard(playerOne.getHand()); //printing out player's initial hand. 
        cout<<endl;
        playerScore = playerOne.checkForPair(playerScore, nonsense); // checking for pairs and deleting from hand and incrementing score
        playerOne.setScore(playerScore); // setting the score
        cout<<"\nPlayer's initial hand after checking for pairs: "<<endl;
        printCard(playerOne.getHand());
        cout<<endl<<endl;
        computerScore = computer.checkForPair(computerScore, nonsense); // checking for pairs for computer and setting to determined score
        computer.setScore(computerScore); // setting score to computerScore
        do { 
            //if the number of cards in either player's hand runs low, we'll add card to it as a "GO FISH"
            if( playerOne.lowDeck() ) {
                playerOne.goFish(deck);
            } 
            if(computer.lowDeck()) {
                computer.goFish(deck);
            }
            //player's turn. 
            cout<<"\nWhich card would you like to ask the computer for? \nChoose a index next to the card of your choice."<<endl; 
            printCard(playerOne.getHand());
            cin>>choosenIndex; //player chooses the index of the card.
            while( (choosenIndex < 1) || (choosenIndex > playerOne.getHand().size())) {
                cout<<"Invalid Input. Enter correct Index associated with the card."<<endl;
                cin>>choosenIndex;
            }
            while(playerOne.askForCard(computer, choosenIndex) ) { // determines if other player has that card, returns true or false
                cout<<"\nPlayer's hand before checking for pair"<<endl;
                printCard(playerOne.getHand());
                playerScore = playerOne.checkForPair(playerScore, nonsense); // checking for pairs and deleting from hand and incrementing score, nonsence is the recursion helper varibale. 
                playerOne.setScore(playerScore); // setting the score
                cout<<"\nplayer's hand after checking for pair."<<endl;
                if(playerOne.getHand().size() == 0 ){  //if the player is out of card, it goes fishing. 
                    playerOne.goFish(deck);
                }
                cout<<"\nWhich card would you like to ask the computer for? \nChoose a index next to the card of your choice."<<endl;
                printCard(playerOne.getHand()); 
                cin>>choosenIndex; // as long as the player keep getting pairs, it can continue to ask for cards from the computer. 
                while( (choosenIndex < 1) || (choosenIndex > playerOne.getHand().size())) {
                    cout<<"Invalid Input. Enter correct Index associated with the card."<<endl;
                    cin>>choosenIndex;
                }
            }
            //player asked for a card that will computer don;t have. So that's the end of it's turn. 
            playerOne.goFish(deck); // a card from the deck is addded to the hand. 
            cout<<"\nPlayer's hand before checking for pair"<<endl;
            printCard(playerOne.getHand());
            playerScore = playerOne.checkForPair(playerScore, nonsense); // checking for pairs and deleting from hand and incrementing score
            playerOne.setScore(playerScore); // setting the score
            cout<<"\nplayer's hand after checking for pair."<<endl;
            printCard(playerOne.getHand());
            
            //computer's turn starts. 
            srand(time(0));
            choosenIndex = (rand() % computer.getHand().size() ) +1; // the index for the computer is choosen random. 
            cout<<"\nComputer asked for: "<<endl;
            printCurrentCard(computer.getHand().at(choosenIndex-1));// printing out the card that was asked for. 
            while(computer.askForCard(playerOne, choosenIndex) ) { // determines if other player has that card, returns true or false
                computerScore = computer.checkForPair(computerScore, nonsense); // checking for pairs and deleting from hand and incrementing score
                computer.setScore(computerScore); // setting the score
                if(computer.getHand().size() == 0 ){ //if the computer's deck runs low, computer goes fishing. 
                    computer.goFish(deck);
                }
                choosenIndex = (rand() % computer.getHand().size() ) +1; //randomly choosen index for computer. 
                cout<<"\nComputer asked for: "<<endl;
                printCurrentCard(computer.getHand().at(choosenIndex-1)); //printing out a single card.  
            }
            computer.goFish(deck); // a card from the deck is addded to the hand. 
            cout<<"\nComputer went fishing."<<endl;
            computerScore = computer.checkForPair(computerScore, nonsense); // checking for pairs and deleting from hand and incrementing score
            computer.setScore(computerScore); // setting the score
        } while(deck.size() > 5 ); //as long as there are five or more cards in the deck, the game goes on. 
        // reason behind choosing five cards is, during the game at most five cards are being extracted from the deck. We don;t want a out of range thrown in the middle of the game. 
        
        cout<<"Computer has "<<computerScore<<" pairs, and the player has "<<playerScore<<" pairs."<<endl;
        gamelog<<"TIME: "<<asctime(timeinfo)<<"  Computer pairs: "<<computerScore<<"  Player pairs: "<<playerScore;
        if (playerScore > computerScore) {
            cout<<"player wins"<<endl;
            gamelog<<"   player wins"<<endl;
        }
        else if (playerScore < computerScore) {
            cout<<"computer wins"<<endl;
            gamelog<<"   computer wins"<<endl;
        }
        else {
            cout<<"TIE" << endl; 
            gamelog<<"   TIE"<<endl; 
        }
        cout<<"Do you want to play again? (Yes or No) "<<endl;
        cin>>again;
    }
    gamelog.close();
  
     
}