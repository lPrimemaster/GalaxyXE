#include "entity.h"
#include <stdexcept>

Entity::Entity(Model & model)
{
	this->model = &model;
}

Entity::~Entity()
{
}

Model & Entity::getModel()
{
	return *model;
}

Texture & Entity::getTexture()
{
	return *texture;
}

void Entity::setPosition(glm::vec3 newPos)
{
	position = newPos;
	translation = glm::translate(glm::mat4(1.0f), position);
}

glm::mat4 Entity::getModelMatrix()
{
	//rotation_ammount += 0.01f;
	return translation * rotation * scale;
}
