#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vmath.h>

#define BUFFER_OFFSET(BufferOffset) ((void*)(BufferOffset))

class Program
{
public:
	Program();
	~Program();

	GLuint& getProgram();
	void build();
	void use();

private:
	GLuint program;
};

