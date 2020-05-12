#pragma once
#include "Entity.h"
class Enemy : public Entity
{
	float attackDelay = 0;
	float visibility = 100.f;
	float speed = 200;
	void animation(float time);
	void draw(RenderTarget& target, RenderStates states) const;
public:
	Enemy(float startX, float startY, float Width, float Height, std::string filename);
	void input(Entity* ent, float time);
	void update(float time);
};