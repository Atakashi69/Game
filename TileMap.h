#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"

using namespace std;
using namespace sf;

#define WALL '#'
#define DIRT ' '
#define EXIT 'E'
#define MONSTER 'M'

class TileMap : public Transformable, public Drawable
{
	vector<vector<Sprite>> level;
	vector<vector<char>> CMAP;
	Texture texture;
	int width = 0, height = 0;
	int levelnum = 0;
	list<Enemy*> enemies;
public:
	Vector2f getSize();
	TileMap(int levelNum = 0);
	void loadFromFile(int levelNum);
	void updateCollision(Entity* ent, float time);
	void updateEnemies(Entity* ent, float time);
	void draw(RenderTarget& target, RenderStates states) const;
};