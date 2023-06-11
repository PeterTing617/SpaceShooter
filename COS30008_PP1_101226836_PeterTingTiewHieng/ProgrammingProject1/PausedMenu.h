#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace sf;
using namespace std;

class PausedMenu
{
private:
	Font font;
	Text pauseText;
	RectangleShape background;

	void initFonts();

public:
	// Constructor and destructor
	PausedMenu(RenderWindow& w);
	virtual ~PausedMenu();

	// functions
	void render(RenderTarget &target);
};

