#include "Enemy.h"

#include <iostream>

void Enemy::input(Entity* ent, float time)
{
	float Pleft = ent->rect.left;
	float Pright = ent->rect.left + ent->rect.width;
	float Ptop = ent->rect.top;
	float Pbottom = ent->rect.top + ent->rect.height;

	float Tleft = this->rect.left;
	float Tright = this->rect.left + this->rect.width;
	float Ttop = this->rect.top;
	float Tbottom = this->rect.top + this->rect.height;

	FloatRect area(rect.left - visibility, rect.top - visibility, rect.width + visibility * 2, rect.height + visibility * 2);
	if (ent->rect.intersects(area))
	{
		//Hunting
		visibility = 350.f;
		if (Pleft + 10 > Tright || Pright - 10 < Tleft)
		{
			if (Pleft + 10 > Tright)
				velocity.x = speed;
			if (Pright - 10 < Tleft)
				velocity.x = -speed;
		}
		else {
			if (Ptop + 10 > Tbottom)
				velocity.y = speed;
			if (Pbottom - 10 < Ttop)
				velocity.y = -speed;
		}

		if (ent->rect.intersects(this->rect) && !ent->immunity)
		{
			ent->health -= 1;
			ent->immunity = true;
		}
		if (ent->immunity)
		{
			attackDelay += time;
			if (attackDelay > 0.5f)
			{
				ent->immunity = false;
				attackDelay = 0;
			}
		}
	}
	else
	{
		visibility = 250.f;
	}

	rect.left += velocity.x * time;
	rect.top += velocity.y * time;
}

void Enemy::animation(float time)
{
	float animationSpeed = 0.03f;
	currentFrame += speed * animationSpeed * time;
	if (currentFrame >= 4.f)
		currentFrame = 0;

	if (velocity.x < 0.f)
		sprite.setTextureRect(IntRect(16 * (int)currentFrame, 22, 16, 22)); //left
	else if (velocity.x > 0.f)
		sprite.setTextureRect(IntRect(16 * (int)currentFrame, 66, 16, 22)); //right
	else if (velocity.y < 0.f)
		sprite.setTextureRect(IntRect(16 * (int)currentFrame, 0, 16, 22)); //up
	else if (velocity.y > 0.f)
		sprite.setTextureRect(IntRect(16 * (int)currentFrame, 44, 16, 22)); //down
	else
		sprite.setTextureRect(IntRect(16 * int(currentFrame), 44, 16, 22)); //idle
}

void Enemy::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &texture;
	target.draw(sprite, states);
}

Enemy::Enemy(float startX, float startY, float Width, float Height, std::string filename)
{
	this->texture.loadFromFile(filename);
	sprite.setTexture(texture);
	sprite.scale(4, 4);
	sprite.setTextureRect(IntRect(16, 44, Width, Height));
	rect = FloatRect(startX, startY, Width * 4, Height * 4);
}
void Enemy::update(float time)
{
	animation(time);
	sprite.setPosition(rect.left, rect.top);
	velocity.x = velocity.y = 0;
}