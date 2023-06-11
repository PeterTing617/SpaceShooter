#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace sf;
using namespace std;

enum button_states {
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};

class Button
{
private:
	RectangleShape shape;
	Font* font;
	Text text;

	Color txtIdleColor;
	Color txtHoverColor;
	Color txtActiveColor;

	Color idleColor;
	Color hoverColor;
	Color activeColor;

	short unsigned buttonState;

public:
	// Constructor and Destructor
	Button(float x, float y, float width, float height, Font* f, string txt, Color textIdle, Color textHover, Color textActive, Color idleC, Color hoverC, Color activeC, int size, Color outline = Color::Transparent, float outlinethickness = 0.f);
	virtual ~Button();

	// Accessors
	bool isPressed();

	// Functions
	void update(const Vector2f& mousePos);

	void render(RenderTarget& target);
};