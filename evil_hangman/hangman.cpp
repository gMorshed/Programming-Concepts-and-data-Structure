/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Gazi Morshed

    last modified: 9/24/2017
*/
#include<iostream>
#include "hangman.h"
#include <fstream>
#include<map>
#include<string>
#include<set>
using namespace std;

// constructor
hangman::hangman() { 
    // TODO: Read in and store words from dictionary.txt
    // TODO: Initialize game state variables
    ifstream fin;  //reading in all the words from the dictionary. 
    fin.open("dictionary.txt");
    if (!fin) {
		cerr << "Error opening file" << endl;
    }
    while(!fin.eof()){
        string str;
        int len;
        fin>>str;
        len = str.size();
        //sorting all the words into a map according to their length. 
        if(_words.count(len)){
            _words.at(len).push_back(str);
        }
        else {
            vector<string> temp;
            temp.push_back(str);
            _words.emplace(len, temp);
        }
    }
    wanted_guess =0;
    fin.close();
}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses) {  //DONE
    wanted_guess = num_guesses; //set the num of guesses to the guess number in the class
    int len;
    cout<<"What length of word do you want?"<<endl;
    cin>>len;
    cout<<endl;
    while( !_words.count(len)){ //check if we have word of that length in the dictionary.
        cout<<"I don't have any word of that length. Try again"<<endl;
        cin>>len;
    }
    for(int i=0; i<len; i++){ // initializing this word with the same length as the user wanted but all with '-'. As the game progresses and the user make correct guess,I will update that
        word_to_display +="-";
    }
    
    
    _wordList = _words.at(len); //making a word list which containing all the words that is currently being searched for the guessed char. 
    // first time around word list contains all the words of the lenght wanted, then word list will contain the words from the desired key of the word family map.
}


// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) { //magic happens here!!!!
    _wordFamily.clear();   
    vector<string> temp_word_list = make_word_family(c); //I will call the make word family function to convert all the words currently in play into a stipped version
    //which will only show the instances where the guessed letter is present. 
    for(int i=0; i<_wordList.size(); i++){
        if(_wordFamily.count(temp_word_list[i])){ //I create a new map of word family each and every time the user guess a letter with the key being the stripped version
        //where the letter occures and the values being all the word with subsiquent keys. 
            _wordFamily.at(temp_word_list[i]).push_back(_wordList[i]);
        }
        else{
            vector<string>temp;
            temp.push_back(_wordList[i]);
            _wordFamily.emplace(temp_word_list[i], temp );
        }
    }
    string key;
    vector<string> temp;
    int max=0;
    for(map <string,vector<string>>::iterator it = _wordFamily.begin(); it != _wordFamily.end(); it++) {  //this determines which map key has the most amount of words as we will work with that key for the next iteration.  
        if(_wordFamily.at(it->first).size() > max){
            max = _wordFamily.at(it->first).size();
            key = it->first; //I need to know which key and the vector of strings corresponding to that key
            temp = it->second;
        }
    }
    _wordList = temp; //word list gets updated to the new words that we will look at for next iteration. 
    
    for(int i=0; i<key.size(); i++){
        if(key[i] == c){
            word_to_display[i] = c; // if the guessed char is available in the key that we have choosen, then the word to display gets updated
            
        }
    }
    
    for(auto x: word_to_display){
        if(x == c){ //if the word to display contains the guessed letter by the user, then we will add that to the list of guessed letters and return true. 
            guessed_letters.emplace(c);
            return true;
        }
    }
    guessed_letters.emplace(c);
    wanted_guess--; //if they guess it wrong, guess remaining decreases. 
    word_to_win = temp[0]; //when the user loses, I just choose the first word in the currently running vector of strings as if I chose that word.
    return false;
    
}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return word_to_display;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() { //DONE
    return wanted_guess;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {   //DONE
    string str="";
    for(auto x: guessed_letters){ //have to convert the set into a string to display as a word. 
        str += x;
    }
    return str;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    for(auto x: guessed_letters){
        if(x ==c){// if the letter that they guessed is in the set of guessed letters that I am keeping track of, it will return true. 
            return true;
        }
    }
    return false;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    for(map <string,vector<string>>::iterator it = _wordFamily.begin(); it != _wordFamily.end(); it++) { // if the word that I am going to display is the same as any word in the current vector of words, user won. 
        vector<string> temp = _wordFamily.at(it->first);
        for(int i =0; i<temp.size(); i++ ){
            if(temp[i] == word_to_display){
                return true;
            }
        }
    }
    return false;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    if(wanted_guess < 1){ //guess becomes 0, they lose. 
        return true;
    }
    return false;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    return word_to_win; // the "word" that they are trying to guess. 
}


vector<string> hangman::make_word_family(char a){ //this function takes in the letter the user guessed, and turn all the instances of the words currently in play into that letter with the rest being a '-'    
    vector<string> temp_word_list = _wordList;
    for(int i=0; i<temp_word_list.size(); i++) {
        for(int j=0; j<temp_word_list[i].size(); j++) {
            if(temp_word_list[i][j] == a){
                temp_word_list[i][j] = a;
            }
            else {
                temp_word_list[i][j] = '-';
            }
        }
    }
    return temp_word_list;
}

int hangman::get_num_word_rem(){ //returns the size of the word list which represents how many words are remaning in the guess list. 
    return _wordList.size(); //
}