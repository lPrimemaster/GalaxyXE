#pragma once
#include "../Models/loader.h"
#include "../Models/model.h"
#include "../Textures/texture.h"
#include "../Entities/entity.h"
#include "../camera.h"

class Skybox : public Entity
{
public:
	Skybox();
	~Skybox();

private:
	Loader loader;
	std::vector<glm::vec3> vertices;
};

