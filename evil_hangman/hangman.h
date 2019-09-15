#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h
        
    Class definition for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman        

    author: 

    last modified: 9/24/2017
*/
#include<set>
#include <string>
#include<map>
#include<vector>
using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
    hangman();

    // start a new game where player gets num_guesses unsuccessful tries
	void start_new_game(int num_guesses);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    string get_display_word();

    // How many guesses remain?
	int get_guesses_remaining();

    // What characters have already been guessed (for display)?
    string get_guessed_chars();

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();
    
    //show number of words remaining
    int get_num_word_rem();

    // Return the true hidden word.
    string get_hidden_word(); 
     

private:
    map<int, vector<string>> _words; //all the words from the dictionary into this map
    int wanted_guess; //how many guess they want
    set<char> guessed_letters; //this set keeps track of all the word that the user already gueesed
    vector<string> _wordList; //this vector chnages everytime the user guess a letter. this vector represents the words currently in play. 
    map< string, vector<string>> _wordFamily; //this map is consists of all the word family key and the words corrresonding to them 
    string word_to_display;
    string word_to_win;
    vector<string> make_word_family(char a); //this function turns the words into a version of their key. 
};

#endif
