#include "sshader.h"



StaticShader::StaticShader()
	: Program("base", "base")
{
	getUniformLocations();
}

StaticShader::StaticShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	: Program(vertexShaderFile, fragmentShaderFile)
{
	getUniformLocations();
}

void StaticShader::setProjViewMatrix(const glm::mat4 & matrix)
{
	loadMatrix4f(m_locationProjViewMatrix, matrix);
}

void StaticShader::setModelMatrix(const glm::mat4 & matrix)
{
	loadMatrix4f(m_locationModelMatrix, matrix);
}

void StaticShader::loadSampler(int unit, int texture)
{
	int loc = glGetUniformLocation(getID(), "sampler");
	glActiveTexture(GL_TEXTURE0 + unit);
	glUniform1i(loc, texture);
}

void StaticShader::setTime(float time)
{
	loadFloat(m_locationTime, time);
}

void StaticShader::getUniformLocations()
{
	m_locationProjViewMatrix = glGetUniformLocation(getID(), "ProjView");
	m_locationModelMatrix = glGetUniformLocation(getID(), "Model");
	m_locationTime = glGetUniformLocation(getID(), "t");
	printf("Model matrix location: %d\n", m_locationModelMatrix);
	printf("ProjView matrix location: %d\n", m_locationProjViewMatrix);
}
