#pragma once
#include "StateBase.h"

class StateStack
{
private:
	StateBase* fElements[10];
	int fStackPointer;
	int fStackSize;

public:
	// Constructor and destructor
	StateStack();
	~StateStack();

	// functions
	// Check whether it's empty
	bool isEmpty() const;

	// Check the size of the array
	int size() const;

	// Push a state into fElements
	void push(StateBase* item);

	// Pop a state from fElements
	void pop();

	// Get the top state from fElements
	StateBase* top();
};

