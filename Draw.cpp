#include "Engine.h"

void Engine::draw()
{
	window.clear(Color(0,0,0));

	window.draw(*tilemap);
	window.draw(*player);
	window.draw(*enemy);

	window.display();
}