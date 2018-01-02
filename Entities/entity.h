#pragma once
#include "../Models/model.h"
#include "../Models/loader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class Entity
{
public:
	Entity() = default;
	Entity(Model& model);
	~Entity();

	Model& getModel();
	Texture& getTexture();

	void setPosition(glm::vec3 newPos);
	glm::mat4 getModelMatrix();

	void operator()(Model* model)
	{
		this->model = model;
	}

	void operator()(Texture* texture)
	{
		this->texture = texture;
	}

	void operator<<(float scale)
	{
		this->scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	}

	void operator<<(glm::vec3 rotationDegrees)
	{
		this->rotation = glm::rotate(rotation, glm::radians(rotationDegrees.x), glm::vec3(1.0f, 0.0f, 0.0f)); //X-Axis Rotation
		this->rotation = glm::rotate(rotation, glm::radians(rotationDegrees.y), glm::vec3(0.0f, 1.0f, 0.0f)); //Y-Axis Rotation
		this->rotation = glm::rotate(rotation, glm::radians(rotationDegrees.z), glm::vec3(0.0f, 0.0f, 1.0f)); //Y-Axis Rotation
	}

protected:
	Model* model;
	Texture* texture;

private:
	glm::vec3 position;

	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 translation = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);
};

