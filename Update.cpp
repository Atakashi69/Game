#include "Engine.h"

void Engine::update(float time)
{
	if (!gameState) return;
	player->input(time);
	tilemap->updateCollision(player, time);
	player->update(view, time);

	tilemap->updateEnemies(player, time);

	if (player->health <= 0)
		gameState = false;
}