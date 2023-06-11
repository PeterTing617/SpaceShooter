#pragma once

#include "Entity.h"

class PowerUps:public Entity
{
	string type;

public:
	PowerUps(Texture* texture, Vector2f scale, Vector2u windowBounds, float speed, string t);
	~PowerUps();

	// Accessors
	string getType();
};

