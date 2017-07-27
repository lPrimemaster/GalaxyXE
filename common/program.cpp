#include "program.h"



Program::Program()
{
	program = glCreateProgram();
}


Program::~Program()
{
}

GLuint & Program::getProgram()
{
	return program;
}

void Program::build()
{
	glLinkProgram(program);
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	std::cout << "Link status for shaders " << ": / ";
	if (!status)
	{
		std::cout << "ERROR" << std::endl;

		//Show log with error
		GLint len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		std::cout << log << std::endl;
		delete log;
	}
	else
	{
		std::cout << "LINKED" << std::endl;
	}
}

void Program::use()
{
	glUseProgram(program);
}
