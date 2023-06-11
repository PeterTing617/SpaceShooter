#pragma once

#include "Entity.h"

class Enemy:public Entity
{
private:
	int hp;
	int damage;

public:
	// Constructor and destructor
	Enemy(Texture *texture, Vector2f scale, Vector2u windowBounds, float enemySpeed, int enemyHP, int dmg);
	~Enemy();

	// Accessors
	int getHP();
	int getDamage();

	// Friend Operator Overload
	friend Enemy& operator-=(Enemy& e, int dmg);
};

