#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "program.h"

class Shader
{
public:
	Shader(GLenum type, const char* path);
	~Shader();

	void link(Program p);
	GLuint& getProgram();
	GLenum getType();

private:
	GLuint shader;
	GLuint programID;
	GLenum type;

	const char* path;
	const GLchar* readFile(const char* path);
};

