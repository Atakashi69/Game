#include "Engine.h"

Engine::Engine()
{
	window.create(VideoMode(800, 600), "title", Style::Close);
	window.setVerticalSyncEnabled(true);
	player = new Player(300, 300, 16, 22, "assets/player.png");
	enemy = new Enemy(400, 400, 16, 22, "assets/enemy.png");
	tilemap = new TileMap("assets/maps/level0.txt");
}

void  Engine::start()
{
	Clock clock;

	float leftBorder = 500;
	float rightBorder = tilemap->getSize().x * 128 - leftBorder;
	float topBorder = 500;
	float bottomBorder = tilemap->getSize().y * 128 - topBorder;

	while (window.isOpen())
	{
		float time = clock.restart().asSeconds();
		view.setCenter(floor(player->getPosition().x), floor(player->getPosition().y));

		if (view.getCenter().x < leftBorder)
			view.setCenter(leftBorder, view.getCenter().y);
		if (view.getCenter().y < topBorder)
			view.setCenter(view.getCenter().x, topBorder);

		if(player->getPosition().x > rightBorder)
			view.setCenter(rightBorder, view.getCenter().y);

		if (player->getPosition().y > bottomBorder)
			view.setCenter(view.getCenter().x, bottomBorder);

		window.setView(view);

		input();
		update(time);
		draw();
	}
}

Engine::~Engine()
{
	delete tilemap;
	delete player;
	delete enemy;
}