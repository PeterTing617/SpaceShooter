#include "GameOverMenu.h"

void GameOverMenu::initFonts()
{
	if (!font.loadFromFile("Fonts/Lato-Regular.ttf")) {
		throw("Game over font could not load font");
	}
}

GameOverMenu::GameOverMenu(RenderWindow& w)
{
	initFonts();
	background.setSize(Vector2f(static_cast<float>(w.getSize().x), static_cast<float>(w.getSize().y)));
	background.setFillColor(Color(20, 20, 20, 100));

	gameOverText.setFont(font);
	gameOverText.setFillColor(Color(255, 255, 255, 200));
	gameOverText.setCharacterSize(60);
	gameOverText.setString("GAME OVER");
	gameOverText.setPosition(125.f, 250.f);

	scoreText.setFont(font);
	scoreText.setFillColor(Color(255, 255, 255, 200));
	scoreText.setCharacterSize(60);
	scoreText.setPosition(190.f, 425.f);

	escapeText.setFont(font);
	escapeText.setFillColor(Color(255, 255, 255, 200));
	escapeText.setCharacterSize(20);
	escapeText.setString("Press ESCAPE to return to Main Menu");
	escapeText.setPosition(135.f, 600.f);

	retryText.setFont(font);
	retryText.setFillColor(Color(255, 255, 255, 200));
	retryText.setCharacterSize(20);
	retryText.setString("Press R to return to retry");
	retryText.setPosition(190.f, 700.f);
}

GameOverMenu::~GameOverMenu()
{
}

void GameOverMenu::render(RenderTarget& target, string score)
{
	target.draw(background);

	scoreText.setString("Score: " + score);

	target.draw(gameOverText);
	target.draw(scoreText);
	target.draw(escapeText);
	target.draw(retryText);
}
