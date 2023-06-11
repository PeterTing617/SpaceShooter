#pragma once

#include "GameState.h"
#include "MainMenuState.h"
#include "StateStack.h"

class Game
{
private:
	// Variables
	RenderWindow *window;
	Event sfEvent;

	Clock dtClock;
	float dt;

	StateStack states;

	// Initialization
	void initWindow();
	void initStates();

	// Constructors / Destructors
	Game();
	virtual ~Game();

public:
	// static instance for game class
	static Game* instance;
	// static instance for game 
	static Game* sharedInstance();

	// Functions
	void endApplication();
	// Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	// Render
	void render();

	// Core
	void run();
};

