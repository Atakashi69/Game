#pragma once
#include "Entity.h"

class Player : public Entity
{
	Font font;
	Text healthText;
	RectangleShape healthRect;
	RectangleShape healthRectOutline;
	float speed = 300;
	void animation(float time);
	void draw(RenderTarget& target, RenderStates states) const;
public:
	Vector2f getPosition();
	Player(int startX, int startY, int Width, int Height, std::string filename);
	void input(float time);
	void update(View& view, float time);
};