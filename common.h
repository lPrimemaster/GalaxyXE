#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Entity;
class Texture;

namespace loader
{
	GLuint shaderLoader(const std::string& vertexShader, const std::string& fragmentShader);

	glm::vec3 parseVec3(const char* buffer);
	glm::vec2 parseVec2(const char* buffer);

	Texture * loadTexture2D(std::string& filename);
}

namespace initializer
{
	std::pair<Entity, std::string> makePair(Entity entity, std::string identifier);
	bool createContext(GLFWwindow* window, glm::uvec2 resolution, const char* title);
	void checkContext(bool contextret);
}