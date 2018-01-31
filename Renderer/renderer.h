#pragma once
#include <map>
#include "../Entities/entity.h"
#include "../Shaders/sshader.h"
#include "../Textures/texture.h"

#define GXE_BIND 0x01
#define GXE_UNBIND 0x02

class Camera;

class Renderer
{
public:
	Renderer(const Renderer&& renderer) = delete; //Not movable
	Renderer() = default;

	void push(Entity* entity);
	void remove(Entity* entity);

	void push(Light* light);
	void remove(Light* light);

	virtual void update(Camera& camera) = 0;
	virtual void draw() = 0;

protected:
	std::vector<Entity*> entities;
	std::vector<Light*> lights;
	
};

