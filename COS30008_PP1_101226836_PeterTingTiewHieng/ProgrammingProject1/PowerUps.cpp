#include "PowerUps.h"

PowerUps::PowerUps(Texture* texture, Vector2f scale, Vector2u windowBounds, float speed, string t):Entity(texture,scale,windowBounds,speed)
{
	type = t;
}

PowerUps::~PowerUps()
{
}

string PowerUps::getType()
{
	return type;
}
