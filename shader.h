#pragma once
#include <iostream>
#include "common/program.h"

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

