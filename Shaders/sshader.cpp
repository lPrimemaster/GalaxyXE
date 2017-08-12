#include "sshader.h"



SShader::SShader()
	: Program("Base", "Base")
{
	getUniformLocations();
}

SShader::SShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	: Program(vertexShaderFile, fragmentShaderFile)
{
	
}

void SShader::setProjViewMatrix(const vmath::mat4 & matrix)
{
	loadMatrix4f(m_locationProjViewMatrix, matrix);
}

void SShader::setModelMatrix(const vmath::mat4 & matrix)
{
	loadMatrix4f(m_locationModelMatrix, matrix);
}

void SShader::getUniformLocations()
{
	m_locationProjViewMatrix = glGetUniformLocation(getID(), "ProjView");
	m_locationModelMatrix = glGetUniformLocation(getID(), "Model");
}
