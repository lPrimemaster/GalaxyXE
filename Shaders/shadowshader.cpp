#include "shadowshader.h"

ShadowShader::ShadowShader() : Program("shadowmap", "shadowmap")
{
	getUniformLocations();
}

ShadowShader::ShadowShader(const std::string & vertexShaderFile, const std::string & fragmentShaderFile) : Program(vertexShaderFile, fragmentShaderFile)
{
}

void ShadowShader::setCurrentLight(Light * const light)
{
	cLight = light;
}

void ShadowShader::setModelMatrix(const glm::mat4 & matrix)
{
	loadMatrix4f(m_locationMVP, matrix);
}

void ShadowShader::getUniformLocations()
{
	m_locationMVP = glGetUniformLocation(getID(), "depthMVP");
}
