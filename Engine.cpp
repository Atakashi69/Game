#include "Engine.h"

Engine::Engine()
{
	window.create(VideoMode(800, 600), "title", Style::Close);
	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(false);
	player = new Player(300, 300, 16, 22, "assets/player.png");
	tilemap = new TileMap;
}

void  Engine::start()
{
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.restart().asSeconds();
		view.setCenter(floor(player->getPosition().x), floor(player->getPosition().y));

		float leftBorder = 500;
		float rightBorder = tilemap->getSize().x * 128 - leftBorder;
		float topBorder = 500;
		float bottomBorder = tilemap->getSize().y * 128 - topBorder;

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
}