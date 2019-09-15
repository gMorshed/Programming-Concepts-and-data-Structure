/*
    CSCI 262 Data Structures, Spirng 18, Project 4 - Markov Chain

    map_model.cpp

    Class implimentation for map_model

    Author: Gazi Morshed

*/

#include <cstdlib>
#include <vector>
#include <map>
#include<vector>
#include<string>
#include<cstdlib>
#include "map_model.h"

using namespace std;


void map_model::initialize(std::string text, int order){
    _data = text + text.substr(0, _order); //this is done for the algorithm, don't know why. 
	_order = order;
	for(int i=0; i<_data.size(); i++){ // go through the whole data set, and put together a map. 
	    string sub = _data.substr(i,_order); // that's the key. 
	    if(marko.count(sub)){ //if the if exist. 
	        marko[sub].push_back(_data[i+_order]); // add the value to that key
	    }
	    else{
	        vector<char>temp;
	        temp.push_back(_data[i+_order]);
	        marko.emplace(sub,temp);//if the key doesn't exist, make the key along with the value.  
	    }
	}
}
string map_model::generate(int size){ //this method generates the string that is to be returned as an answer to the main this model. 
    int start = rand() % (_data.length() - _order); //randomly pick a starting point and making sure it's in bound. 
    string seed = _data.substr(start, _order); //seed in this case is basically the key of the map we made for this model. 
    string answer="";
    for (int i = 0; i < size; i++) { //
        int char_seed =rand()% marko[seed].size(); // each and every key has a lot of values associated with it which are stored as a vector. pick one randomly. 
        answer += marko[seed].at(char_seed); //add that random one to the answer. 
        seed = _data.substr(i+1+start, _order);// //update seed by moving the char forawd in the stream of the string. 
    }
    return answer;
}