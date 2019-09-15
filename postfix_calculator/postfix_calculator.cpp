/*
	postfix_calculator.cpp

	Implementation of the postfix calculator. 

    CSCI 262, Spring 2018, Project 2

	author: 
*/

#include "postfix_calculator.h"
#include <string>
#include<stack>
#include<sstream>
#include<cmath>

using namespace std;

postfix_calculator:: postfix_calculator(){ //this is the default constructor. There is only one member variable in my code. But I don't want to set anything to the stack.
	//that the user didn't put inn. 
}
bool postfix_calculator::evaluate(string expr) {   
    istringstream string_in(expr); //making a string stream
    string str;
    double result_op;
    while(!string_in.eof()) {
    	string_in>>str; //read in the string
    	if(str == "+") { //if the string is "postive" sign, we will do calculation 
    		if(calc_stack.size() < 2){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{ //as long as there are at least two elements, we will add the top two elements in the stack.
    			result_op = calc_stack.top();
    			calc_stack.pop();
    			result_op += calc_stack.top();
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	else if(str == "-") {
    		if(calc_stack.size() < 2){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{  //perform calculation with the top two elements in the stack.
    			result_op = calc_stack.top(); 
    			calc_stack.pop();
    			result_op = calc_stack.top() - result_op;
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	else if(str =="*") {
    		if(calc_stack.size() < 2){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{ //perform calculation with the top two elements in the stack.
    			result_op = calc_stack.top();
    			calc_stack.pop();
    			result_op *= calc_stack.top();
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	else if(str =="/") {
    		if(calc_stack.size() < 2){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{ //perform calculation with the top two elements in the stack.
    			result_op = calc_stack.top();
    			calc_stack.pop();
    			result_op = calc_stack.top() / result_op;
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	else if(str == "^"){
    		if(calc_stack.size() < 2){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{ //perform calculation with the top two elements in the stack.
    			result_op = calc_stack.top();
    			calc_stack.pop();
    			result_op = pow(calc_stack.top(), result_op);
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	
    	else if(str == "sqrt"){
    		if(calc_stack.size() < 1){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{ //perform calculation with the top two elements in the stack.
    			result_op = sqrt(calc_stack.top());
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	else if(str == "log"){
    		if(calc_stack.size() < 1){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{ //perform calculation with the top two elements in the stack.
    			result_op = log10(calc_stack.top());
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	
    	else if(str == "ln"){
    		if(calc_stack.size() < 1){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{ //perform calculation with the top two elements in the stack.
    			result_op = log(calc_stack.top());
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	
    	else if(str == "sin"){
    		if(calc_stack.size() < 1){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{ //perform calculation with the top two elements in the stack.
    			result_op = sin(calc_stack.top());
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	
    	else if(str == "cos"){
    		if(calc_stack.size() < 1){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{ //perform calculation with the top two elements in the stack.
    			result_op = cos(calc_stack.top());
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	
    	else if(str == "tan"){
    		if(calc_stack.size() < 1){ //I need at least two element to perform this calculation
    			return false;
    		}
    		else{ //perform calculation with the top two elements in the stack.
    			result_op = tan(calc_stack.top());
    			calc_stack.pop();
    			calc_stack.emplace(result_op);
    		}
    	}
    	
    	
    	else{
    		double d = stod(str); // turn the string into a double
    		calc_stack.emplace(d); //add this string into the double. 
    	}
    }
    return true;
}

void postfix_calculator::clear() { //clearing out the stack. 
	while(!calc_stack.empty()){ //empty out the stack
		calc_stack.pop();
	}
}

double postfix_calculator::top(){
	if(!calc_stack.empty()){ //if the stack isn't empty, return the top element
		return calc_stack.top();
	}
	else{
		return 0.0; // if the stack is empty, return 0.0
	}
}

string postfix_calculator::to_string() { // return all the elements in the stack as a string
	string s="";
	stack<double>temp_stack = calc_stack;
	while(!temp_stack.empty()){
		s = s+ " " + std::to_string(temp_stack.top());
		temp_stack.pop();
	}
	return s;
}

