#pragma once

#include "StateBase.h"
#include "PowerUps.h"
#include "DifficultyList.h"
#include "PausedMenu.h"
#include "GameOverMenu.h"

class GameState :
    public StateBase
{
private:
    Font font;
    Music gameMusic;
    RectangleShape background;
    
    // Game Timer
    int timer;
    int gameTimer;

    // Menu
    PausedMenu pmenu;
    GameOverMenu gmenu;

    // Player
    Player* player;
    
    // Level
    DifficultyList dl;
    bool losed;
    int currentLevel;

    //Enemy
    vector<Enemy> enemies;
    int spawnTimer;

    //PowerUps
    vector<PowerUps> powerUps;
    int powerTimer;

    // Texts
    Text healthText;
    Text currentWeaponText;
    Text scoreText;
    Text timerText;

    void initTexture();
    void initBackground();
    void initFonts();
    void initMusic();
    void initPlayer();
    void initUI();
    void initDifficulty();
public:
    // Constructor and destructor
    GameState(RenderWindow* w);
    virtual ~GameState();

    // Functions
    void UIUpdate();
    void DifficultyUpdate();
    void updateInput(const float& dt);
    void update(const float& dt);
    void drawUI(RenderTarget* target);
    void render(RenderTarget* target = nullptr);
};

