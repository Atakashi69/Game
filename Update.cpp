#include "Engine.h"

void Engine::update(float time)
{
	if (!gameState) return;
	player->input(time);
	tilemap->updateCollision(player);
	player->update(view, time);

	enemy->input(player, time);
	tilemap->updateCollision(enemy);
	enemy->update(time);

	if (player->health <= 0)
		gameState = false;
}