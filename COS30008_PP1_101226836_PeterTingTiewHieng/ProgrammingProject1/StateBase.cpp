#include "StateBase.h"

StateBase::StateBase(RenderWindow* w)
{
	window = w;
	quit = false;
	pause = false;
	switchState = false;
	keyTime = 0.f;
	keyTimeMax = 10.f;
	switchTarget = "";
}

StateBase::~StateBase()
{
}

bool StateBase::getQuit()
{
	return quit;
}

bool StateBase::getKeytime()
{
	if (keyTime >= keyTimeMax) {
		keyTime = 0.f;
		return true;
	}
	else {
		return false;
	}
}

bool StateBase::getSwitchState()
{
	return switchState;
}

string StateBase::getSwitchTarget()
{
	return switchTarget;
}

void StateBase::endState()
{
	quit = true;
}

void StateBase::paused()
{
	pause = true;
}

void StateBase::unpaused()
{
	pause = false;
}

void StateBase::reverseSwitch()
{
	switchState = false;
}

void StateBase::updateMousePositions()
{
	mousePosView = window->mapPixelToCoords(Mouse::getPosition(*window));
}

void StateBase::updateKeytime(const float& dt)
{
	if (keyTime < keyTimeMax) {
		keyTime += 100.f * dt;
	}
}

void StateBase::playMusic()
{
}