#include "MainMenuState.h"

void MainMenuState::initTexture()
{
	if (!textures["MAIN_MENU_BACKGROUND"].loadFromFile("Resources/Background/mainBackground.jpg")) {
		throw "Main Menu cannot load background";
	}
}

void MainMenuState::initMusic()
{
	menuMusic.openFromFile("Resources/Audio/menu.ogg");
	menuMusic.setVolume(100);
}

void MainMenuState::initBackground()
{
	background.setSize(Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
	background.setTexture(&textures["MAIN_MENU_BACKGROUND"]);

	credit.setFont(font);
	credit.setCharacterSize(10);
	credit.setFillColor(Color::White);
	credit.setPosition(230, 950);
	credit.setString("Project for COS30008 - 101226836");
}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile("Fonts/Lato-Regular.ttf")) {
		throw("MainMenuState could not load font");
	}
}

void MainMenuState::initButtons()
{
	buttons.push_back(new Button(200.f, 450.f, 200.f, 60.f, &font, "Start Game", Color(70, 70, 70, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50), Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0), 45, Color(250, 250, 250, 250),3));

	buttons.push_back(new Button(200.f, 600.f, 200.f, 60.f, &font, "Quit", Color(70, 70, 70, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),  Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0), 45, Color(250, 250, 250, 250), 3));
}

MainMenuState::MainMenuState(RenderWindow* w) :StateBase(w)
{
	initTexture();
	initMusic();
	initFonts();
	initBackground();
	initButtons();
	menuMusic.play();
	menuMusic.setLoop(true);
}

MainMenuState::~MainMenuState()
{
	for (ButtonIterator iter(buttons); iter != iter.end(); ++iter) {
		delete (*iter);
	}
}

void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons()
{
	// Updates all buttons in the state and handle their functions
	for (ButtonIterator iter(buttons); iter != iter.end(); ++iter) {
		(*iter)->update(mousePosView);
	}

	// Game State
	if (buttons[0]->isPressed()) {
		switchState = true;
		switchTarget = "Start Game";
		menuMusic.stop();
	}

	// Quit
	if (buttons[1]->isPressed()) {
		endState();
		menuMusic.stop();
	}
}

void MainMenuState::update(const float& dt)
{
	updateMousePositions();
	updateButtons();
}

void MainMenuState::renderButtons(RenderTarget* target)
{
	for (ButtonIterator iter(buttons); iter != iter.end(); ++iter) {
		(*iter)->render(*target);
	}
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target) {
		target = window;
	}

	target->draw(background);

	renderButtons(target);

	target->draw(credit);
}

void MainMenuState::playMusic()
{
	menuMusic.play();
	menuMusic.setLoop(true);
}
