#pragma once

#include "Weapon.h"

class Missile : public Weapon
{
private:

public:
	// Constructor and destructor
	Missile() {}

	Missile(Texture* texture, Vector2f position, float speed, int offsetX, int offsetY, Vector2f scale) :Weapon(texture, position, speed, offsetX, offsetY, scale) {
		weaponDamage = 3;
	};

	virtual ~Missile() {};
};