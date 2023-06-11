#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace sf;
using namespace std;

class GameOverMenu
{
private:
	Font font;
	Text gameOverText;
	Text scoreText;
	Text escapeText;
	Text retryText;
	RectangleShape background;

	void initFonts();

public:
	// Constructor
	GameOverMenu(RenderWindow& w);
	// Destructor
	virtual ~GameOverMenu();

	// functions
	void render(RenderTarget& target, string score);
};

