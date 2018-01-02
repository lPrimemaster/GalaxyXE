#include "renderer.h"
#include "../camera.h"

void Renderer::push(Entity * entity)
{
	entities.push_back(entity);
}

void Renderer::remove(Entity * entity)
{
	std::vector<Entity*>::iterator it;
	it = entities.begin();
	for (it = entities.begin(); it != entities.end(); it++)
	{
		if (entity == *it)
		{
			entities.erase(it);
			return;
		}
	}
}

