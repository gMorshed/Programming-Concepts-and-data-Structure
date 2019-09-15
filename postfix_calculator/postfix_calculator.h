/*
	postfix_calculator.h

	Header file for the postfix calculator.  

    CSCI 262, Spring 2018, Project 2

	author: 
*/

#ifndef _POSTFIX_CALCULATOR_H
#define _POSTFIX_CALCULATOR_H

#include <string>
#include<stack>

class postfix_calculator {
public:
	bool evaluate(std::string);

	// Remove all items from the current stack.
	void clear();

	// Return the number at the top of the stack (this will be the
	// answer if a valid query was passed to evaluate).  If the
	// stack is empty, returns 0.0.  The number  should *not* be 
	// popped from the stack (this allows further  calculations
	// using this number).
	double top();

	// Return a string representation of the stack showing all the
	// elements in it.  Hint: make a copy of the stack to display
    // the contents of.
	std::string to_string();

	// Constructor
	postfix_calculator();


private:
	// TODO: declare member variables here for your stack, etc.
	std::stack<double> calc_stack;
};

#endif
