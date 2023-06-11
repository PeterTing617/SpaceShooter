#include "GameState.h"

void GameState::initTexture()
{
	if (!textures["BACKGROUND"].loadFromFile("Resources/Background/space.jpg"))
	{
		throw "Game Background cannot load";
	}
	if (!textures["ENEMY"].loadFromFile("Resources/Textures/enemy.png"))
	{
		throw "Enemy Texture cannot load";
	}
	if (!textures["PLAYER"].loadFromFile("Resources/Textures/ship.png"))
	{
		throw "Player Texture cannot load";
	}
	if (!textures["BULLET"].loadFromFile("Resources/Textures/bullet.png"))
	{
		throw "Bullet Texture cannot load";
	}
	if (!textures["MISSLE"].loadFromFile("Resources/Textures/missle.png"))
	{
		throw "Missile Texture cannot load";
	}
	if (!textures["BOMB"].loadFromFile("Resources/Textures/bomb.png"))
	{
		throw "Bomb Texture cannot load";
	}
	if (!textures["BONUS"].loadFromFile("Resources/Textures/bonus.png"))
	{
		throw "Bonus Texture cannot load";
	}
	if (!textures["UPGRADE"].loadFromFile("Resources/Textures/upgrade.png"))
	{
		throw "Upgrade Texture cannot load";
	}
}

void GameState::initBackground()
{
	background.setSize(Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

	background.setTexture(&textures["BACKGROUND"]);
}

void GameState::initFonts()
{
	if (!font.loadFromFile("Fonts/Lato-Regular.ttf")) {
		throw("MainMenuState could not load font");
	}
}

void GameState::initMusic()
{
	gameMusic.openFromFile("Resources/Audio/backmusic.ogg");
	gameMusic.setVolume(100);
}

void GameState::initPlayer()
{
	player = new Player(260, 650, &textures["PLAYER"], &textures["BULLET"], &textures["MISSLE"], &textures["BOMB"], Vector2f(1.f, 1.f));
}

void GameState::initUI()
{
	healthText.setFont(font);
	healthText.setCharacterSize(13);
	healthText.setFillColor(Color::White);

	currentWeaponText.setFont(font);
	currentWeaponText.setCharacterSize(13);
	currentWeaponText.setFillColor(Color::White);

	scoreText.setFont(font);
	scoreText.setCharacterSize(25);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(0, 0);

	timerText.setFont(font);
	timerText.setCharacterSize(25);
	timerText.setFillColor(Color::White);
	timerText.setPosition(0, 50);
}

void GameState::initDifficulty()
{
	dl.insertDifficulty(4, 4, 225.f, 25, 50, 40, 5, 80, 485); // last
	dl.insertDifficulty(3, 3, 200.f, 20, 60, 60, 4, 85, 490);
	dl.insertDifficulty(2, 2, 175.f, 15, 70, 80, 3, 90, 495);
	dl.insertDifficulty(1, 1, 150.f, 10, 80, 100, 2, 95, 500); // first
}

GameState::GameState(RenderWindow* w):StateBase(w),pmenu(*w),gmenu(*w)
{
	initTexture();
	initBackground();
	initFonts();
	initMusic();
	initPlayer();
	initDifficulty();
	initUI();

	timer = 0;
	gameTimer = timer;

	spawnTimer = dl.getHead()->spawnTimerMax;

	powerTimer = dl.getHead()->powerUpTimerMax;
	
	currentLevel = 1;

	losed = false;

	gameMusic.play();
	gameMusic.setLoop(true);
}

GameState::~GameState()
{
	delete player;
}

void GameState::UIUpdate()
{
	healthText.setPosition(player->getPosition().x + 2.f, player->getPosition().y + 60.f);
	healthText.setString("HP: " + player->getHpAsString());

	currentWeaponText.setPosition(player->getPosition().x + 12.f, player->getPosition().y + 80.f);
	currentWeaponText.setString(player->getCurrentWeapon());

	scoreText.setString("Score: " + player->getScoreAsString());

	timerText.setString("Timer: " + to_string(gameTimer));
}

void GameState::DifficultyUpdate()
{
	if (gameTimer == 20 && currentLevel == 1)
	{
		currentLevel++;
		dl.nextLevel();
	}
	if (gameTimer == 40 && currentLevel == 2)
	{
		currentLevel++;
		dl.nextLevel();
	}
	if (gameTimer == 60 && currentLevel == 3)
	{
		currentLevel++;
		dl.nextLevel();
	}
}

void GameState::updateInput(const float& dt)
{
	if (!losed)
	{
		if (Keyboard::isKeyPressed(Keyboard::P) && getKeytime()) {
			if (!pause)
			{
				paused();
				gameMusic.pause();
			}
			else {
				unpaused();
				gameMusic.play();
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape) && getKeytime() && pause) {
			endState();
			gameMusic.stop();
		}
	}
	else {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			endState();
		}
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			switchState = true;
			switchTarget = "Restart Game";
		}
	}
}

void GameState::update(const float& dt)
{
	updateMousePositions();
	updateKeytime(dt);
	updateInput(dt);
	// Player have not lose
	if (!losed)
	{
		// unpaused
		if (!pause)
		{
			// Update game timer and spawn timer
			timer++;
			gameTimer = int(timer / 120);

			if (spawnTimer < dl.getReached()->spawnTimerMax)
			{
				spawnTimer++;
			}
			if (powerTimer < dl.getReached()->powerUpTimerMax)
			{
				powerTimer++;
			}

			// Difficulty update
			DifficultyUpdate();

			// Player Update
			player->update(dt, enemies);

			// Enemy Update
			for (size_t i = 0; i < enemies.size(); i++)
			{
				enemies[i].update(dt);
				if (enemies[i].getGlobalBounds().intersects(player->getGlobalBounds()))
				{
					int takenDamage = enemies[i].getDamage();
					enemies.erase(enemies.begin() + i);
					player->takeDmg(takenDamage);
					return;
				}
				if (enemies[i].getPosition().y > window->getSize().y)
				{
					enemies.erase(enemies.begin() + i);
					return;
				}
			}

			// PowerUps Update
			for (size_t i = 0; i < powerUps.size(); i++)
			{
				powerUps[i].update(dt);
				if (powerUps[i].getGlobalBounds().intersects(player->getGlobalBounds()))
				{
					player->getUpgrade(powerUps[i].getType());
					powerUps.erase(powerUps.begin() + i);
					return;
				}
				if (powerUps[i].getPosition().y > window->getSize().y)
				{
					powerUps.erase(powerUps.begin() + i);
					return;
				}
			}

			// Enemy Spawner
			if (enemies.size() < size_t(dl.getReached()->maxEnemies))
			{
				if ((rand() % 100) + 1.0 >= dl.getReached()->spawnChance && spawnTimer >= dl.getReached()->spawnTimerMax)
				{
					enemies.push_back(Enemy(&textures["ENEMY"], Vector2f(4.f, 4.f), window->getSize(), dl.getReached()->enemyMovementSpeed, dl.getReached()->enemyHP, dl.getReached()->enemyDamage));
					spawnTimer = 0;
				}
			}

			//PowerUp Spawner
			if (powerUps.size() < size_t(dl.getReached()->maxPower))
			{
				if ((rand() % 100) + 1.0 >= dl.getReached()->powerUpChance && powerTimer >= dl.getReached()->powerUpTimerMax)
				{
					if ((rand() % 100) + 1.0 > 50)
					{
						powerUps.push_back(PowerUps(&textures["BONUS"], Vector2f(1.f, 1.f), window->getSize(), 200.f, "BONUS"));
					}
					else {
						powerUps.push_back(PowerUps(&textures["UPGRADE"], Vector2f(1.f, 1.f), window->getSize(), 200.f, "UPGRADE"));
					}
					powerTimer = 0;
				}
			}

			// UI update
			UIUpdate();

			// Check health
			if (player->isDead())
			{
				losed = true;
			}
		}
		else {
			// paused
		}
	}
	else {
		// Player lose
		gameMusic.stop();
	}
}

void GameState::drawUI(RenderTarget* target)
{
	target->draw(healthText);
	target->draw(currentWeaponText);
	target->draw(scoreText);
	target->draw(timerText);
}

void GameState::render(RenderTarget* target)
{
	if (!target) {
		target = window;
	}
	// Render background
	target->draw(background);
	// Render player
	player->render(target);
	// Render enemies
	for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i].render(target);
	}
	// Render powerUps
	for (size_t i = 0; i < powerUps.size(); i++)
	{
		powerUps[i].render(target);
	}
	// Render UI
	drawUI(target);
	// Render pause
	if (pause)
	{
		pmenu.render(*target);
	}
	// Render gameOver
	if (losed)
	{
		gmenu.render(*target, player->getScoreAsString());
	}
}
