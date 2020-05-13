#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Player.h"
#include "Enemy.h"
#include "TileMap.h"

using namespace std;
using namespace sf;

class Engine
{
	RenderWindow window;
	View view;
	Player* player = nullptr;
	TileMap* tilemap = nullptr;
	bool gameState = true;

	void input();
	void update(float time);
	void draw();
public:
	Engine();
	~Engine();
	void start();
};