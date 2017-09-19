#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GL/glew.h>

class Camera
{
public:
	Camera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);
	void lookAt(glm::vec3 eye, glm::vec3 center);
	const glm::mat4 getViewMatrix() const;
	const glm::mat4 getProjectMatrix() const;
	const glm::mat4 getProjViewMatrix() const;




	void debug();

private:
	GLfloat m_fov;
	GLfloat m_aspect;
	GLfloat m_planes[2];
	enum Planes {near, far};

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectMatrix;
};

