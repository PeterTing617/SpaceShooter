#pragma once
#include "Weapon.h"
class Bomb :
    public Weapon
{
private:

public:
	// Constructor and destructor
	Bomb() {}

	Bomb(Texture* texture, Vector2f position, float speed, int offsetX, int offsetY, Vector2f scale) :Weapon(texture, position, speed, offsetX, offsetY, scale) {
		weaponDamage = 10;
	};

	virtual ~Bomb() {};
};

