#include "StateStack.h"

StateStack::StateStack()
{
	for (size_t i = 0; i < 10; i++)
	{
		fElements[i] = nullptr;
	}
	fStackPointer = 0;
	fStackSize = 10;
}

StateStack::~StateStack()
{
	for (size_t i = 0; i < 10; i++)
	{
		delete fElements[i];
	}
}

bool StateStack::isEmpty() const
{
	return fStackPointer == 0;
}

int StateStack::size() const
{
	return fStackPointer;
}

void StateStack::push(StateBase* item)
{
	if (fStackPointer < fStackSize)
	{
		fElements[fStackPointer++] = item;
	}
	else {
		throw overflow_error("Stack full");
	}
}

void StateStack::pop()
{
	if (!isEmpty())
	{
		fStackPointer--;
	}
	else {
		throw underflow_error("Stack empty");
	}
}

StateBase* StateStack::top()
{
	if (!isEmpty())
	{
		return fElements[fStackPointer - 1];
	}
	else {
		throw underflow_error("Stack empty");
	}
}
