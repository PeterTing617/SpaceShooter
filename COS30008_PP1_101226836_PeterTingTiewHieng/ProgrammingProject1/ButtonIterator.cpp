#include "ButtonIterator.h"

ButtonIterator::ButtonIterator(vector<Button*> b, int start)
{
	btns = b;
	fLength = b.size();
	fIndex = start;
}

ButtonIterator::~ButtonIterator()
{
}

Button* ButtonIterator::operator*()
{
	return btns[fIndex];
}

ButtonIterator& ButtonIterator::operator++()
{
	fIndex++;
	return *this;
}

ButtonIterator ButtonIterator::operator++(int)
{
	ButtonIterator temp = *this;
	fIndex++;
	return temp;
}

bool ButtonIterator::operator==(const ButtonIterator& aOther) const
{
	return (fIndex == aOther.fIndex) && (btns == aOther.btns);
}

bool ButtonIterator::operator!=(const ButtonIterator& aOther) const
{
	return !(*this == aOther);
}

ButtonIterator ButtonIterator::begin() const
{
	return ButtonIterator(btns);
}

ButtonIterator ButtonIterator::end() const
{
	return ButtonIterator(btns, fLength);
}

