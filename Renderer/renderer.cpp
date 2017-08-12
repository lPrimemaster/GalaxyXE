#include "renderer.h"
#include "../camera.h"

Renderer::Renderer(std::vector<std::pair<Entity, std::string>> data)
{
	for (auto& px : data)
	{
		auto emplace = entities.emplace(px.first, px.second);
		identifier.push_back(emplace.first);
	}
}

void Renderer::push(std::pair<Entity, std::string> EntityID)
{
	auto emplaced = entities.emplace(EntityID.first, EntityID.second);
	identifier.push_back(emplaced.first);
}

void Renderer::update(Camera & camera)
{
}

void Renderer::draw()
{
	for (auto& entID : entities)
	{
		entID.first.getModel().;
	}
}
