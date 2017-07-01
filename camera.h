#pragma once
#include "shader.h"
#include "types.h"

class Camera
{
public:
	Camera(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far, GLboolean ortho);
	void lookAt(vmath::vec3 eye, vmath::vec3 center, vmath::vec3 up);
	vmath::mat4 & getView();
	vmath::mat4 & getProject();
	~Camera();
private:
	GLfloat fov;
	GLfloat aspect;
	GLfloat planes[2];
	enum Planes {near, far};

	vmath::mat4 view;
	vmath::mat4 project;
};

