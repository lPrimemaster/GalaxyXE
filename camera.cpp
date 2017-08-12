#include "camera.h"



Camera::Camera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far)
{
	this->m_fov = vmath::radians(fov);
	this->m_aspect = aspect;
	this->m_planes[this->near] = near;
	this->m_planes[this->far] = far;

	m_viewMatrix = vmath::lookat(vmath::vec3(0, 0, -(far + 1)), vmath::vec3(0, 0, 0), vmath::vec3(0, 1, 0));
	m_projectMatrix = vmath::perspective(this->m_fov, this->m_aspect, this->m_planes[this->near], this->m_planes[this->far]);

}

void Camera::lookAt(vmath::vec3 eye, vmath::vec3 center, vmath::vec3 up)
{
	m_viewMatrix = vmath::lookat(eye, center, up);
}

vmath::mat4 Camera::getViewMatrix() const
{
	return m_viewMatrix;
}

vmath::mat4 Camera::getProjectMatrix() const
{
	return m_projectMatrix;
}

