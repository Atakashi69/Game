#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "Entity.h"

using namespace std;
using namespace sf;

#define WALL '#'
#define DIRT ' '

class TileMap : public Transformable, public Drawable
{
	vector<vector<Sprite>> level;
	vector<vector<char>> CMAP;
	Texture texture;
	int width = 0, height = 0;

public:
	Vector2f getSize();
	TileMap(string filename);
	void updateCollision(Entity* ent);
	void draw(RenderTarget& target, RenderStates states) const;
};

