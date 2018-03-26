#include "skyshader.h"



SkyShader::SkyShader() : Program("skyshader", "skyshader")
{
	
}


SkyShader::~SkyShader()
{
}

void SkyShader::setProjViewMatrix(const glm::mat4& matrix)
{
	loadMatrix4f(m_locationProjViewMatrix, matrix);
}

void SkyShader::getUniformLocations()
{
	m_locationProjViewMatrix = glGetUniformLocation(getID(), "ProjView");
}
