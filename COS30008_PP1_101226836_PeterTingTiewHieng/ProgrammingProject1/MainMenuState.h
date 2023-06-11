#pragma once

#include "StateBase.h"
#include "ButtonIterator.h"

class MainMenuState :
    public StateBase
{
private:
    // Attributes
    RectangleShape background;
    Font font;
    Music menuMusic;
    Text credit;

    vector<Button*> buttons;

    // Functions
    void initTexture();
    void initMusic();
    void initBackground();
    void initFonts();
    void initButtons();

public:
    // Constructor and destructor
    MainMenuState(RenderWindow* w);
    virtual ~MainMenuState();

    // Functions
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(RenderTarget* target = nullptr);
    void render(RenderTarget* target = nullptr);
    void playMusic();
};

