#include "Player.h"

void Player::initMusic()
{
	bullet_buffer.loadFromFile("Resources/Audio/bullet.wav");
	bullet_sound.setBuffer(bullet_buffer);

	missile_buffer.loadFromFile("Resources/Audio/missile.wav");
	missile_sound.setBuffer(missile_buffer);

	bomb_buffer.loadFromFile("Resources/Audio/plantBomb.wav");
	bomb_sound.setBuffer(bomb_buffer);

	explosion_buffer.loadFromFile("Resources/Audio/explosion.wav");
	explosion_sound.setBuffer(explosion_buffer);

	crash_buffer.loadFromFile("Resources/Audio/crash.ogg");
	crash_sound.setBuffer(crash_buffer);

	changeWeapon_buffer.loadFromFile("Resources/Audio/changeWeapon.wav");
	changeWeapon_sound.setBuffer(changeWeapon_buffer);

	powerUps_buffer.loadFromFile("Resources/Audio/upgrade.wav");
	powerUps_sound.setBuffer(powerUps_buffer);
}

Player::Player(float x, float y, Texture* playerTxt, Texture* bulletTxt, Texture* missleTxt, Texture* bombTxt, Vector2f scale)
{
	initMusic();
	playerTexture = playerTxt;
	bulletTexture = bulletTxt;
	missleTexture = missleTxt;
	bombTexture = bombTxt;
	playerSprite.setTexture(*playerTexture);
	playerSprite.setScale(scale);
	playerSprite.setPosition(x, y);

	// Add int symbolise weapons to wheel
	wheel.addWeaponsAfterSelected(0, 25, "Bullet");
	wheel.addWeaponsAfterSelected(1, 75, "Missile");
	wheel.addWeaponsBeforeSelected(-1, 150, "Bomb");

	score = 0;

	hp = 10;
	hpMax = 10;

	shootTimer = wheel.readRate();
	changeTimerMax = 50;
	changeTimer = changeTimerMax;
	damageTimerMax = 25;
	damageTimer = damageTimerMax;
	upgradeTimer = 0;
	movementSpeed = 300.f;
}

Player::~Player()
{
}

FloatRect Player::getGlobalBounds()
{
	return playerSprite.getGlobalBounds();
}

Vector2f Player::getPosition()
{
	return playerSprite.getPosition();
}

String Player::getHpAsString()
{
	return to_string(hp) + "/" + to_string(hpMax);
}

String Player::getCurrentWeapon()
{
	return wheel.readName();
}

String Player::getScoreAsString()
{
	return to_string(score);
}

bool Player::isDead()
{
	if (hp <= 0) {
		explosion_sound.play();
		return true;
	}
	else {
		return false;
	}
}

void Player::Combat()
{
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		if (shootTimer >= wheel.readRate())
		{
			if (wheel.readID() == 0)
			{
				if (upgradeTimer > 0)
				{
					playerAttack.push_back(Bullet(bulletTexture, playerSprite.getPosition(), 350, 0, 0, Vector2f(0.5f, 0.5f)));
					playerAttack.push_back(Bullet(bulletTexture, playerSprite.getPosition(), 350, 32, 0, Vector2f(0.5f, 0.5f)));
				}
				else {
					playerAttack.push_back(Bullet(bulletTexture, playerSprite.getPosition(), 350, 16, -25, Vector2f(0.5f, 0.5f)));
				}
				bullet_sound.play();
				shootTimer = 0;
			}
			if (wheel.readID() == 1)
			{
				if (upgradeTimer > 0)
				{
					playerAttack.push_back(Missile(missleTexture, playerSprite.getPosition(), 250, 0, 0, Vector2f(1.f, 1.f)));
					playerAttack.push_back(Missile(missleTexture, playerSprite.getPosition(), 250, 32, 0, Vector2f(1.f, 1.f)));
				}
				else {
					playerAttack.push_back(Missile(missleTexture, playerSprite.getPosition(), 250, 16, -25, Vector2f(1.f, 1.f)));
				}
				missile_sound.play();
				shootTimer = 0;
			}
			if (wheel.readID() == -1)
			{
				if (upgradeTimer > 0)
				{
					playerAttack.push_back(Bomb(bombTexture, playerSprite.getPosition(), 0, 16, -25, Vector2f(4.f, 4.f)));
				}
				else {
					playerAttack.push_back(Bomb(bombTexture, playerSprite.getPosition(), 0, 16, -25, Vector2f(2.f, 2.f)));
				}
				bomb_sound.play();
				shootTimer = 0;
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::E)) {
		if (changeTimer >= changeTimerMax)
		{
			wheel.selectNext();
			changeWeapon_sound.play();
			changeTimer = 0;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		if (changeTimer >= changeTimerMax)
		{
			wheel.selectPrevious();
			changeWeapon_sound.play();
			changeTimer = 0;
		}
	}
}

void Player::movement(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		if (playerSprite.getPosition().y >= 0)
		{
			playerSprite.move(0.f * movementSpeed * dt, -1.f * movementSpeed * dt);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (playerSprite.getPosition().x >= -32)
		{
			playerSprite.move(-1.f * movementSpeed * dt, 0.f * movementSpeed * dt);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		if (playerSprite.getPosition().y <= 940)
		{
			playerSprite.move(0.f * movementSpeed * dt, 1.f * movementSpeed * dt);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (playerSprite.getPosition().x <= 568)
		{
			playerSprite.move(1.f * movementSpeed * dt, 0.f * movementSpeed * dt);
		}
	}
}

void Player::takeDmg(int dmg)
{
	if (damageTimer >= damageTimerMax)
	{
		hp -= dmg;
		damageTimer = 0;
		crash_sound.play();
	}
}

void Player::getUpgrade(string t)
{
	powerUps_sound.play();
	if (t == "BONUS")
	{
		if (hp < hpMax)
		{
			hp += 1;
		}
	}
	if (t == "UPGRADE")
	{
		upgradeTimer = 1000;

	}
}

void Player::update(const float& dt, vector<Enemy>& enemies)
{
	// Update all timers
	if (shootTimer < wheel.readRate())
	{
		shootTimer++;
	}
	if (changeTimer < changeTimerMax)
	{
		changeTimer++;
	}
	if (damageTimer < damageTimerMax)
	{
		damageTimer++;
	}
	if (upgradeTimer >= 0)
	{
		upgradeTimer--;
	}

	// Bullets update
	for (size_t i = 0; i < playerAttack.size(); i++)
	{
		playerAttack[i].update(dt);

		// Enemy collision check
		for (size_t j = 0; j < enemies.size(); j++)
		{
			if (playerAttack[i].getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
			{
				int giveDmg = playerAttack[i].getDamage();

				playerAttack.erase(playerAttack.begin() + i);

				if (enemies[j].getHP() >= 1)
				{
					// Enemy take damage, otherwise destroyed
					enemies[j] -= giveDmg;
					if (enemies[j].getHP() <= 0)
					{
						explosion_sound.play();
						enemies.erase(enemies.begin() + j);
						score += 1;
					}
				}
				return;
			}
		}

		if (playerAttack[i].getPosition().y < -32)
		{
			playerAttack.erase(playerAttack.begin() + i);
			return;
		}
	}
	Combat();
	movement(dt);
}

void Player::render(RenderTarget* target)
{
	target->draw(playerSprite);
	for (size_t i = 0; i < playerAttack.size(); i++)
	{
		playerAttack[i].render(target);
	}
}
