#pragma once

#include "WeaponWheel.h"
#include "Bullet.h"
#include "Missile.h"
#include "Bomb.h"
#include "Enemy.h"

class Player
{
private:
	// Sound effects
	SoundBuffer bullet_buffer;
	Sound bullet_sound;
	SoundBuffer missile_buffer;
	Sound missile_sound;
	SoundBuffer bomb_buffer;
	Sound bomb_sound;
	SoundBuffer explosion_buffer;
	Sound explosion_sound;
	SoundBuffer crash_buffer;
	Sound crash_sound;
	SoundBuffer changeWeapon_buffer;
	Sound changeWeapon_sound;
	SoundBuffer powerUps_buffer;
	Sound powerUps_sound;

	// Textures
	Texture* playerTexture;
	Texture* bulletTexture;
	Texture* missleTexture;
	Texture* bombTexture;
	Sprite playerSprite;

	// Weapons
	WeaponWheel wheel;
	vector<Weapon> playerAttack;

	// Player Variables
	int shootTimer;
	int changeTimer;
	int changeTimerMax;
	int damageTimer;
	int damageTimerMax;
	float movementSpeed;
	int upgradeTimer;

	int hp;
	int hpMax;

	int score;

	void initMusic();

public:
	// Constructir and Destructor
	Player(float x, float y, Texture* playerTxt, Texture* bulletTxt, Texture* missleTxt, Texture* bombTxt, Vector2f scale);
	~Player();

	// Accessors
	FloatRect getGlobalBounds();
	Vector2f getPosition();
	String getHpAsString();
	String getCurrentWeapon();
	String getScoreAsString();
	bool isDead();

	// Functions
	void Combat();
	void movement(const float& dt);
	void takeDmg(int dmg);
	void getUpgrade(string t);
	void update(const float& dt, vector<Enemy>& enemies);
	void render(RenderTarget* target);
};
