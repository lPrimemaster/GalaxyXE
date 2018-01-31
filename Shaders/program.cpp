#include "program.h"

Program::Program(const std::string & vertexShaderFile, const std::string & fragmentShaderFile)
	: m_programID(loader::shaderLoader(vertexShaderFile, fragmentShaderFile))
{
	bind();
	std::cout << "[ENGINE] Program compiled and linked successfully." << std::endl;
}

Program::~Program()
{
	glDeleteProgram(m_programID);
}

void Program::bind()
{
	glUseProgram(m_programID);
}

void Program::unbind()
{
	glUseProgram(0);
}

GLuint Program::getID() const
{
	return m_programID;
}

void Program::loadInt(GLuint location, int value)
{
	glUniform1i(location, value);
}

void Program::loadFloat(GLuint location, float value)
{
	glUniform1f(location, value);
}

void Program::loadVector2f(GLuint location, const glm::vec2 vector)
{
	glUniform2f(location, vector.x, vector.y);
}

void Program::loadVector3f(GLuint location, const glm::vec3 vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Program::loadMatrix4f(GLuint location, const glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}
