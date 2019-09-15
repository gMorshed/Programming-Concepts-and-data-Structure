/*
    CSCI 262 Data Structures, Spirng 18, Project 4 - Markov Chain

    map_model.h

    Class declaration for map_model

    Author: Gazi Morshed

*/



#pragma once 

#include "model.h"
#include <cstdlib>
#include <vector>
#include <map>
#include<string>
using namespace std;


class map_model: public markov_model {  //inherit from the markkov model
    public:
	// give the model the example text and the model order; the model
	// should do any preprocessing in this call
	virtual void initialize(std::string text, int order);

	// produce a text in the style of the example
	virtual std::string generate(int size);

protected:
	std::string _data;
	int _order;
	map<string, vector<char> > marko;
};