#include "Game.h"

Game* Game::instance = 0;

void Game::initWindow()
{
    ifstream ifs("Config/window.ini");
    
    string title = "None";
    VideoMode window_bounds(800,600);
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    int style = Style::Close;

    if (ifs.is_open()) {
        getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> style;
    }

    ifs.close();

	window = new RenderWindow(window_bounds, title, style);
    window->setFramerateLimit(framerate_limit);
    window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
    states.push(new MainMenuState(window));
}

Game::Game()
{
    initWindow();
    initStates();
}

Game* Game::sharedInstance()
{
    if (instance == 0) {
        instance = new Game();
    }
    return instance;
}

Game::~Game()
{
	delete window;

    while (!states.isEmpty()) {
        delete states.top();
        states.pop();
    }
}

void Game::endApplication()
{
    cout << "Ending Application" << endl;
}

void Game::updateDt()
{
    // Update dt variable with time to update and render one frame
    dt = dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (window->pollEvent(sfEvent))
    {
        if (sfEvent.type == Event::Closed)
            window->close();
    }
}

void Game::update()
{
    updateSFMLEvents();

    if (!states.isEmpty()) {
        states.top()->update(dt);

        if (states.top()->getSwitchState()) {
            if (states.top()->getSwitchTarget() == "Start Game")
            {
                states.top()->reverseSwitch();
                states.push(new GameState(window));
            }
            if (states.top()->getSwitchTarget() == "Restart Game")
            {
                states.top()->endState();
                delete states.top();
                states.pop();
                states.push(new GameState(window));
            }
        }

        if (states.top()->getQuit()) {
            states.top()->endState();
            delete states.top();
            states.pop();
            if (!states.isEmpty()) {
                states.top()->playMusic();
            }
        }
    }
    // Application end
    else {
        endApplication();
        window->close();
    }
}

void Game::render()
{
    window->clear();

    // Render items
    if (!states.isEmpty()) {
        states.top()->render();
    }

    window->display();
}

void Game::run()
{
    // Game Loop
    while (window->isOpen())
    {
        updateDt();
        update();
        render();
    }
}

