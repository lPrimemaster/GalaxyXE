#include "camera.h"



Camera::Camera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far, GLboolean ortho)
{
	this->fov = vmath::radians(fov);
	this->aspect = aspect;
	this->planes[this->near] = near;
	this->planes[this->far] = far;

	view = vmath::lookat(vmath::vec3(0, 0, -(far + 1)), vmath::vec3(0, 0, 0), vmath::vec3(0, 1, 0));
	if (!ortho)
	{
		//This is stil badly implemented
		project = vmath::ortho(0, 0, 0, 0, this->planes[this->near], this->planes[this->far]);
	}
	else
	{
		project = vmath::perspective(this->fov, this->aspect, this->planes[this->near], this->planes[this->far]);
	}
}

void Camera::lookAt(vmath::vec3 eye, vmath::vec3 center, vmath::vec3 up)
{
	view = vmath::lookat(eye, center, up);
}

vmath::mat4 & Camera::getView()
{
	return view;
}

vmath::mat4 & Camera::getProject()
{
	return project;
}


Camera::~Camera()
{
}
