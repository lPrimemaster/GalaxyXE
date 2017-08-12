#pragma once
#include <vmath.h>
#include <GL/glew.h>

class Camera
{
public:
	Camera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far);
	void lookAt(vmath::vec3 eye, vmath::vec3 center, vmath::vec3 up);
	vmath::mat4 getViewMatrix() const;
	vmath::mat4 getProjectMatrix() const;

private:
	GLfloat m_fov;
	GLfloat m_aspect;
	GLfloat m_planes[2];
	enum Planes {near, far};

	vmath::mat4 m_viewMatrix;
	vmath::mat4 m_projectMatrix;
};

