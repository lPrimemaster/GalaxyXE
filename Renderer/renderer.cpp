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

void Renderer::push(Light * light)
{
	lights.push_back(light);
}

void Renderer::remove(Light * light)
{
	std::vector<Light*>::iterator it;
	it = lights.begin();
	for (it = lights.begin(); it != lights.end(); it++)
	{
		if (light == *it)
		{
			lights.erase(it);
			return;
		}
	}
}

