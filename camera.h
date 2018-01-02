#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GL/glew.h>
#include "Utils/math.h"

class Camera
{
public:
	Camera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);
	void setYaw(GLfloat value);
	void setPitch(GLfloat value);
	void setEye(glm::vec3 eye);
	void fpsRH();

	const glm::vec3 getEye() const;
	const glm::vec3 heading() const;
	const glm::mat4 getViewMatrix() const;
	const glm::mat4 getProjectMatrix() const;
	const glm::mat4 getProjViewMatrix() const;

private:
	GLfloat m_fov;
	GLfloat m_aspect;
	GLfloat m_planes[2];
	enum Planes {near, far};

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectMatrix;
	glm::vec3 eye;
	glm::vec3 direction;
	const glm::vec3 up;

	GLfloat pitch = 0.0f; //Phi
	GLfloat yaw = 0.0f; //Theta

};
