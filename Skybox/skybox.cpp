#include "skybox.h"



Skybox::Skybox()
{
	const static float SIZE = 500.0f;

	vertices = {
		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),

		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(-SIZE, -SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(-SIZE,  SIZE,  SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),

		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),

		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(-SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE, -SIZE,  SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),

		glm::vec3(-SIZE,  SIZE, -SIZE),
		glm::vec3(SIZE,  SIZE, -SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(SIZE,  SIZE,  SIZE),
		glm::vec3(-SIZE,  SIZE,  SIZE),
		glm::vec3(-SIZE,  SIZE, -SIZE),

		glm::vec3(-SIZE, -SIZE, -SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(SIZE, -SIZE, -SIZE),
		glm::vec3(-SIZE, -SIZE,  SIZE),
		glm::vec3(SIZE, -SIZE,  SIZE)
	};

	this->model = new Model();
	this->texture = new Texture();

	loader.loadRaw(*this->model, vertices);
	loader.loadTextureSB(*this->texture, "nsws");
}


Skybox::~Skybox()
{
}

