#include "TileMap.h"

TileMap::TileMap(int levelNum)
{
	levelnum = levelNum;
	string  levelname = "assets/maps/level";
	levelname.append(std::to_string(levelnum));
	levelname.append(".txt");
	fstream infile(levelname);

	texture.loadFromFile("assets/world.png");

	char c;
	int i = 0, j = 0;
	vector<char> temp;
	while (infile >> noskipws >> c)
	{
		if (c != '\n')
			temp.push_back(c);
		else
		{
			CMAP.push_back(temp);
			temp.clear();
		}
	}
	CMAP.push_back(temp);
	width = temp.size();
	height = CMAP.size();

	level = vector<vector<Sprite>>(width, vector<Sprite>(height));
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (CMAP[j][i] == WALL)
				level[i][j].setTextureRect(IntRect(32, 0, 32, 32));
			else if (CMAP[j][i] == DIRT)
				level[i][j].setTextureRect(IntRect(0, 0, 32, 32));
			else if (CMAP[j][i] == EXIT)
				level[i][j].setTextureRect(IntRect(64, 0, 32, 32));
			else if (CMAP[j][i] == MONSTER)
				enemies.push_back(new Enemy(i * 128, j * 128, 16, 22, "assets/enemy.png"));
			level[i][j].scale(4, 4);
			level[i][j].setTexture(texture);
			level[i][j].setPosition(i * 128, j * 128);
		}
	}
}

void TileMap::loadFromFile(int levelNum)
{
	levelnum = levelNum;
	string levelname = "assets/maps/level";
	levelname.append(std::to_string(levelnum));
	levelname.append(".txt");
	fstream infile(levelname);

	texture.loadFromFile("assets/world.png");

	char c;
	vector<char> temp;
	temp.clear();
	level.clear();
	CMAP.clear();
	enemies.clear();
	while (infile >> noskipws >> c)
	{
		if (c != '\n')
			temp.push_back(c);
		else
		{
			CMAP.push_back(temp);
			temp.clear();
		}
	}
	CMAP.push_back(temp);
	width = temp.size();
	height = CMAP.size();

	level = vector<vector<Sprite>>(width, vector<Sprite>(height));
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (CMAP[j][i] == WALL)
				level[i][j].setTextureRect(IntRect(32, 0, 32, 32));
			else if (CMAP[j][i] == DIRT)
				level[i][j].setTextureRect(IntRect(0, 0, 32, 32));
			else if (CMAP[j][i] == EXIT)
				level[i][j].setTextureRect(IntRect(64, 0, 32, 32));
			else if (CMAP[j][i] == MONSTER)
				enemies.push_back(new Enemy(i * 128, j * 128, 16, 22, "assets/enemy.png"));
			level[i][j].scale(4, 4);
			level[i][j].setTexture(texture);
			level[i][j].setPosition(i * 128, j * 128);
		}
	}
}

void TileMap::updateEnemies(Entity* ent, float time)
{
	for (auto enemy : enemies)
	{
		enemy->input(ent, time);
		updateCollision(enemy, time);
		enemy->update(time);
	}
}

void TileMap::draw(RenderTarget& target, RenderStates states) const
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			target.draw(level[i][j]);
	for (auto enemy : enemies)
		target.draw(*enemy);
}

void TileMap::updateCollision(Entity* ent, float time)
{
	for (int i = ent->rect.left / 128; i < (ent->rect.left + ent->rect.width) / 128; i++)
	{
		for (int j = ent->rect.top / 128; j < (ent->rect.top + ent->rect.height) / 128; j++)
		{
			if (i >= 0 && i < width && j >= 0 && j < height)
			{
				if (CMAP[j][i] == WALL)
				{
					if (ent->velocity.x < 0)
					{
						ent->rect.left = i * 128 + 128;
						ent->velocity.x = 0;
					}
					if (ent->velocity.x > 0)
					{
						ent->rect.left = i * 128 - ent->rect.width;
						ent->velocity.x = 0;
					}
					if (ent->velocity.y < 0)
					{
						ent->rect.top = j * 128 + 128;
						ent->velocity.y = 0;
					}
					if (ent->velocity.y > 0)
					{
						ent->rect.top = j * 128 - ent->rect.height;
						ent->velocity.y = 0;
					}
				}
				if (CMAP[j][i] == EXIT)
				{
					ent->health = 10;
					ent->setPosition(130, 130);
					loadFromFile(1);
				}
			}
		}
	}
}

Vector2f TileMap::getSize() { return Vector2f(width, height); }