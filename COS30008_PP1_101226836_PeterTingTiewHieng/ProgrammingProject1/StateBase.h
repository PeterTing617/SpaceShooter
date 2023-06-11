#pragma once

#include "Player.h"

class StateBase
{
protected:
	RenderWindow* window;
	bool quit;
	bool pause;
	bool switchState;
	string switchTarget;
	float keyTime;
	float keyTimeMax;

	Vector2f mousePosView;

	//Resources
	map<string, Texture> textures;

public:
	// Constructor and destructor
	StateBase(RenderWindow* w);
	virtual ~StateBase();

	// Accessors
	bool getQuit();
	bool getKeytime();
	bool getSwitchState();
	string getSwitchTarget();
	
	// Change variables
	void endState();
	void paused();
	void unpaused();
	void reverseSwitch();

	// Functions
	virtual void updateMousePositions();
	virtual void updateKeytime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = nullptr) = 0;
	virtual void playMusic();
};


