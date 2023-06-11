#pragma once

#include "Button.h"

class ButtonIterator {
private:
	vector<Button*> btns;
	int fLength;
	int fIndex;

public:
	// Constructor and destructor
	ButtonIterator(vector<Button*> b, int start = 0);
	~ButtonIterator();

	// Functions
	// Read the value
	Button* operator*();

	// Increment the index
	ButtonIterator& operator++();
	ButtonIterator operator++(int);

	// Comparison with another same type of iterator
	bool operator==(const ButtonIterator& aOther) const;
	bool operator!=(const ButtonIterator& aOther) const;

	// Get the begin and end of the vector
	ButtonIterator begin() const;
	ButtonIterator end() const;
};

