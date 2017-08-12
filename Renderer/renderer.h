#pragma once
#include <map>
#include "../Entities/entity.h"
#include "../Shaders/sshader.h"

class Camera;

class Renderer
{
public:
	Renderer(const Renderer&& renderer) = delete; //Not movable
	Renderer(std::vector<std::pair<Entity, std::string>> data);

	void push(std::pair<Entity, std::string> EntityID);
	void update(Camera& camera);
	void draw();

private:
	using EntityMap = std::map<Entity, std::string>;
	std::vector<EntityMap::iterator> identifier;

private:
	EntityMap entities;
	SShader m_sshader;
	
};

