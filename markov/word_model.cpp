/*
    CSCI 262 Data Structures, Spirng 18, Project 4 - Markov Chain

    word_model.cpp

    Class implimentation for word_model

    Author: Gazi Morshed

*/


#include <cstdlib>
#include <vector>
#include <map>
#include<vector>
#include<string>
#include<cstdlib>
#include "word_model.h"
#include<sstream>
using namespace std;

void word_model::initialize(string text, int order) {
    istringstream sin(text); //make a stream object of of the text
    _order = order;
    string a;
    while(!sin.eof()){
        sin>>a;
        words.push_back(a); //read in all the word in the stream into a vector. 
    }
    for(int i=0;i<_order;i++){
        words.push_back(words.at(i)); //this is done for the algorithm of the markov chain. 
    }
    for(int i=0; i<words.size()- _order; i++){ //this is where the magic happens. we will initialize the word map. 
        string key="";
        string word_to_add;
        for(int j=i; j<_order+i; j++){
            key =key+ words.at(j)+" "; //key could be made out of multiple words. 
            word_to_add = words.at(j+1); //and we have to keep track of which word we would add to the map for the current key. 
        }
            key.resize(key.size()-1); //getting rid of the space at the end. 
            if(word_marko.count(key)){ //key exist, add value
                word_marko[key].push_back(word_to_add);
            }
            else{ //key doesn't exist, make both
                vector<string>temp;
                temp.push_back(word_to_add);
                word_marko.emplace(key, temp);
            }
    }
    
}
string word_model::generate(int size){ //generating a string made out of the as many words as the size
    int start = rand() % (words.size() - _order); //random start point. 
    string seed="";
    for(int i=0; i<_order; i++){
        seed = seed+words[start+i]+" "; //making the seed. 
    }
    seed.resize(seed.size()-1); //getting rid of the space at the end. 
    string answer;
    for(int i=0; i<size; i++){ //generate a string with as many words as the size
        int word_seed = rand() % word_marko[seed].size(); //many words in the vector of a specific key, choosing one randomly. 
        answer = answer+ word_marko[seed].at(word_seed)+" "; //adding that to the answer. 
        seed.erase(); //update seed
        for(int j=i+1+start; j<_order+i+1+start; j++){ //seed start from where it was before plus one,  and goes upto the order. 
            seed = seed + words[j]+" ";
        }
        seed.resize(seed.size()-1); //get rid of the space. 
    }
    return answer;
}