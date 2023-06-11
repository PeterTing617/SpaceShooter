#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class Weapon
{
protected:
	Texture* weaponTexture;
	Sprite weaponSprite;

	int weaponDamage;
	float weaponSpeed;

public:
	// Constructor and destructor
	Weapon() {
		weaponTexture = nullptr;
		weaponDamage = 0;
		weaponSpeed = 0;
	};

	Weapon(Texture* texture, Vector2f position, float speed, int offsetX, int offsetY, Vector2f scale) {
		weaponTexture = texture;
		weaponSprite.setTexture(*weaponTexture);
		weaponSprite.setScale(scale);
		weaponDamage = 0;
		weaponSpeed = speed;
		weaponSprite.setPosition(position.x + offsetX, position.y + offsetY);
	};

	virtual ~Weapon() {};

	// Accessors
	virtual FloatRect getGlobalBounds() { return weaponSprite.getGlobalBounds(); }
	virtual Vector2f getPosition() { return weaponSprite.getPosition(); }
	int getDamage() { return weaponDamage; }

	// Functions
	virtual void movement(const float& dt) {
		weaponSprite.move(0.f, -1.f * weaponSpeed * dt);

	};

	virtual void update(const float& dt) {
		movement(dt);
	};

	virtual void render(RenderTarget* target) {
		target->draw(weaponSprite);
	};
};

