#include "camera.h"



Camera::Camera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far) : m_fov(glm::radians(fov)), m_aspect(aspect)
{
	this->m_planes[this->near] = near;
	this->m_planes[this->far] = far;

	m_projectMatrix = glm::perspective(m_fov, this->m_aspect, this->m_planes[this->near], this->m_planes[this->far]);
	glDepthRange(this->m_planes[this->near], this->m_planes[this->far]);

	m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	m_viewMatrix = glm::rotate(m_viewMatrix, 0.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
	m_viewMatrix = glm::rotate(m_viewMatrix, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::lookAt(glm::vec3 eye, glm::vec3 center)
{
	m_viewMatrix = glm::lookAt(eye , center, glm::vec3(0.0f, 1.0f, 0.0f));
	//m_viewMatrix = glm::mat4(1.0f); //"Re-Identify" it [In Next Line]
	//m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, eye.x));
	//m_viewMatrix = glm::rotate(m_viewMatrix, eye.y, glm::vec3(-1.0f, 0.0f, 0.0f)); //Rot x
	//m_viewMatrix = glm::rotate(m_viewMatrix, eye.z, glm::vec3(0.0f, 1.0f, 0.0f)); //Rot y
}

const glm::mat4 Camera::getViewMatrix() const
{
	return m_viewMatrix;
}

const glm::mat4 Camera::getProjectMatrix() const
{
	return m_projectMatrix;
}

const glm::mat4 Camera::getProjViewMatrix() const
{
	return m_projectMatrix * m_viewMatrix;
}

void Camera::debug()
{
		printf("View matrix\n");
		for (int i = 0; i < 4; i++)
			printf("%f %f %f %f\n", m_viewMatrix[i][0], m_viewMatrix[i][1], m_viewMatrix[i][2], m_viewMatrix[i][3]);
		printf("Project matrix\n");
		for (int i = 0; i < 4; i++)
			printf("%f %f %f %f\n", m_projectMatrix[i][0], m_projectMatrix[i][1], m_projectMatrix[i][2], m_projectMatrix[i][3]);
}

