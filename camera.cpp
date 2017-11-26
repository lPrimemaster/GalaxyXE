#include "camera.h"



Camera::Camera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far) : m_fov(glm::radians(fov)), m_aspect(aspect), pitch(PI/2), yaw(PI/2), up(glm::vec3(0.0f, 1.0f, 0.0f))
{
	this->m_planes[this->near] = near;
	this->m_planes[this->far] = far;

	eye = glm::vec3(0.0f, 0.0f, -10.0f);
	direction = glm::vec3(0.0f);

	m_projectMatrix = glm::perspective(m_fov, this->m_aspect, this->m_planes[this->near], this->m_planes[this->far]);
	glDepthRange(this->m_planes[this->near], this->m_planes[this->far]);

	m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	m_viewMatrix = glm::rotate(m_viewMatrix, 0.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
	m_viewMatrix = glm::rotate(m_viewMatrix, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::fpsRH()
{
	//Placed in here for now
	if (pitch >= PI - 0.005f) pitch = PI - 0.005f;
	else if (pitch <= 0.005f) pitch = 0.005f;
	if (yaw >= 2 * PI) yaw = 0;
	else if (yaw <= 0) yaw = 2 * PI;

	direction = glm::vec3(glm::cos(yaw) * glm::sin(pitch), glm::cos(pitch), glm::sin(yaw) * glm::sin(pitch));
	//std::cout << "Looking at:" << std::endl;
	//std::cout << "X: " << direction.x << " Y: " << direction.y << " Z: " << direction.z << std::endl;
	m_viewMatrix = glm::lookAt(eye, eye + direction, up);
}

void Camera::setYaw(GLfloat value)
{
	yaw += value;
}

void Camera::setPitch(GLfloat value)
{
	pitch += value;
}

void Camera::setEye(glm::vec3 eye)
{
	this->eye = eye;
}

const glm::vec3 Camera::getEye() const
{
	return eye;
}

const glm::vec3 Camera::heading() const
{
	return direction;
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
