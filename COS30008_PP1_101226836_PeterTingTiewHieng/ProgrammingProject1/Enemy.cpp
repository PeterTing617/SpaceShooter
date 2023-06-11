#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2f scale, Vector2u windowBounds, float enemySpeed, int enemyHP, int dmg):Entity(texture,scale,windowBounds, enemySpeed)
{
	hp = enemyHP;
	damage = dmg;
}

Enemy::~Enemy()
{
}

int Enemy::getHP()
{
	return hp;
}

int Enemy::getDamage()
{
	return damage;
}

Enemy& operator-=(Enemy& e, int dmg)
{
	e.hp -= dmg;
	return e;
}
