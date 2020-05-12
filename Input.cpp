#include "Engine.h"

void Engine::input()
{
	Event eve;
	while (window.pollEvent(eve))
		if (eve.type == Event::Closed)
			window.close();
}