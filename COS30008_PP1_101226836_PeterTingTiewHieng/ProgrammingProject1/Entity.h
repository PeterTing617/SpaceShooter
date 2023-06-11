#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace sf;
using namespace std;

class Entity
{
private:
	Texture* entityTexture;
	Sprite entitySprite;

	float movementSpeed;

public:
	// Constructor and destructor
	Entity(Texture* texture, Vector2f scale, Vector2u windowBounds, float speed);
	~Entity();

	// Accessors
	FloatRect getGlobalBounds();
	Vector2f getPosition();

	// Functions
	void movement(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target);
};

