#include "renderer.h"
#include "../camera.h"

void Renderer::push(Entity * entity)
{
	entities.push_back(entity);
}

