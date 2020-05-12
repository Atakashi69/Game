#include "Player.h"
#include <iostream>

void Player::input(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
			velocity.x += -speed;
		if (Keyboard::isKeyPressed(Keyboard::Right))
			velocity.x += speed;
	}
	else {

		if (Keyboard::isKeyPressed(Keyboard::Up))
			velocity.y += -speed;
		if (Keyboard::isKeyPressed(Keyboard::Down))
			velocity.y += speed;
	}

	rect.left += velocity.x * time;
	rect.top += velocity.y * time;
}

void Player::animation(float time)
{
	float animationSpeed = 0.03f;
	currentFrame += speed * animationSpeed * time;
	if (currentFrame >= 4.f)
		currentFrame = 0;

	if (velocity.x < 0.f)
		sprite.setTextureRect(IntRect(16 * (int)currentFrame, 22, 16, 22)); //left
	else if(velocity.x > 0.f)
		sprite.setTextureRect(IntRect(16 * (int)currentFrame, 66, 16, 22)); //right
	else if(velocity.y < 0.f)
		sprite.setTextureRect(IntRect(16 * (int)currentFrame, 0, 16, 22)); //up
	else if (velocity.y > 0.f)
		sprite.setTextureRect(IntRect(16 * (int)currentFrame, 44, 16, 22)); //down
	else
		sprite.setTextureRect(IntRect(16 * int(currentFrame), 44, 16, 22)); //idle
}

void Player::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &texture;
	//std::cout << target.getView().getCenter().x << ", " << target.getView().getCenter().x << std::endl;

	target.draw(sprite, states);
	target.draw(healthRect);
	target.draw(healthRectOutline);
	target.draw(healthText);
}

Player::Player(int startX, int startY, int Width, int Height, std::string filename)
{
	this->texture.loadFromFile(filename);
	sprite.setTexture(texture);
	sprite.scale(4, 4);
	sprite.setTextureRect(IntRect(16, 44, Width, Height));
	rect = FloatRect(startX, startY, Width * 4, Height * 4);

	healthRect.setFillColor(Color::Red);

	healthRectOutline.setFillColor(Color::Transparent);
	healthRectOutline.setSize(Vector2f(200, 25));
	healthRectOutline.setOutlineThickness(2);

	if (!font.loadFromFile("assets/fonts/pixelfont.ttf"))
		std::cout << "ERROR to load pixelfont.ttf for player" << std::endl;
	healthText.setFont(font);
	healthText.setFillColor(Color::White);
	healthText.setOutlineColor(Color::Black);
	healthText.setOutlineThickness(1);
	healthText.setCharacterSize(24);
}
void Player::update(View& view, float time)
{
	animation(time);
	sprite.setPosition(rect.left, rect.top);
	velocity.x = velocity.y = 0;

	healthRectOutline.setPosition(view.getCenter().x - 480, view.getCenter().y - 480);
	healthRect.setPosition(view.getCenter().x - 480, view.getCenter().y - 480);
	healthText.setPosition(view.getCenter().x - 272.5f, view.getCenter().y - 482.5f);

	healthRect.setSize(Vector2f(20 * health, 25));
	healthText.setString(std::to_string(health));
}

Vector2f Player::getPosition() { return { rect.left, rect.top }; }