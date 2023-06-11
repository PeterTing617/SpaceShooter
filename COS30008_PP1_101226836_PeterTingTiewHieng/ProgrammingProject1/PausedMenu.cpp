#include "PausedMenu.h"

void PausedMenu::initFonts()
{
	if (!font.loadFromFile("Fonts/Lato-Regular.ttf")) {
		throw("MainMenuState could not load font");
	}
}

PausedMenu::PausedMenu(RenderWindow& w)
{
	initFonts();
	background.setSize(Vector2f(static_cast<float>(w.getSize().x), static_cast<float>(w.getSize().y)));
	background.setFillColor(Color(20, 20, 20, 100));

	pauseText.setFont(font);
	pauseText.setFillColor(Color(255, 255, 255, 200));
	pauseText.setCharacterSize(60);
	pauseText.setString("PAUSED");
	pauseText.setPosition(190.f, 430.f);
}

PausedMenu::~PausedMenu()
{
}

void PausedMenu::render(RenderTarget& target)
{
	target.draw(background);

	target.draw(pauseText);
}
