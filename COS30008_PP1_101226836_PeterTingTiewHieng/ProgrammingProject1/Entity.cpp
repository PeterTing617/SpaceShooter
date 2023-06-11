#include "Entity.h"

Entity::Entity(Texture* texture, Vector2f scale, Vector2u windowBounds, float speed)
{
	entityTexture = texture;
	entitySprite.setTexture(*entityTexture);
	entitySprite.setScale(scale);
	float spawnX = rand() % windowBounds.x - entitySprite.getGlobalBounds().width;
	if (spawnX < 0) {
		spawnX = 0;
	}
	entitySprite.setPosition(spawnX, 0);

	movementSpeed = speed;
}

Entity::~Entity()
{
}

FloatRect Entity::getGlobalBounds()
{
	return entitySprite.getGlobalBounds();
}

Vector2f Entity::getPosition()
{
	return entitySprite.getPosition();
}

void Entity::movement(const float& dt)
{
	entitySprite.move(0.f * movementSpeed * dt, 1.f * movementSpeed * dt);
}

void Entity::update(const float& dt)
{
	movement(dt);
}

void Entity::render(RenderTarget* target)
{
	target->draw(entitySprite);
}
