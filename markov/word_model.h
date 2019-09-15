/*
    CSCI 262 Data Structures, Spirng 18, Project 4 - Markov Chain

   word_model.h

    Class declaration of word_model

    Author: Gazi Morshed

*/


#pragma once 

#include "model.h"
#include <cstdlib>
#include <vector>
#include <map>
#include<string>

using namespace std;


class word_model: public markov_model {
    public:
	// give the model the example text and the model order; the model
	// should do any preprocessing in this call
	virtual void initialize(std::string text, int order);

	// produce a text in the style of the example
	virtual std::string generate(int size);

protected:
	vector <string> words;
	int _order;
	map<string, vector<string> > word_marko; //as this is a word model, the key is word, and values are vectors made out of words.   
};