#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Entity : public Transformable, public Drawable
{
protected:
	Texture texture;
	Sprite sprite;
	float currentFrame = 0.f;

public:
	bool immunity = false;
	int health = 10;
	FloatRect rect;
	Vector2f velocity;
};