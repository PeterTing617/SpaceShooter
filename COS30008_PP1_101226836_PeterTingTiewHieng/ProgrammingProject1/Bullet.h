#pragma once

#include "Weapon.h"

class Bullet:public Weapon
{
private:

public:
	// Constructor and destructor
	Bullet() {}

	Bullet(Texture* texture, Vector2f position, float speed, int offsetX, int offsetY, Vector2f scale) :Weapon(texture, position, speed, offsetX, offsetY, scale) {
		weaponDamage = 1;
	};

	virtual ~Bullet() {};
};