#include "sshader.h"



StaticShader::StaticShader() : Program("base", "base")
{
	getUniformLocations();
}

StaticShader::StaticShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) : Program(vertexShaderFile, fragmentShaderFile)
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

void StaticShader::setEyeDir(const glm::vec3 & eyeDirection)
{
	loadVector3f(m_locationEyeDirection, eyeDirection);
}

void StaticShader::setDepthBiasMatrix(const glm::mat4 & matrix)
{
	loadMatrix4f(m_locationDepthBiasMatrix, matrix);
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

void StaticShader::setLight(Light* light)
{
	sendLightProperties(getID(), *light, "light", 0);
}

void StaticShader::getUniformLocations()
{
	m_locationProjViewMatrix = glGetUniformLocation(getID(), "ProjView");
	m_locationModelMatrix = glGetUniformLocation(getID(), "Model");
	m_locationDepthBiasMatrix = glGetUniformLocation(getID(), "depthBias");
	m_locationEyeDirection = glGetUniformLocation(getID(), "EyeDirection");

	//Move glUniform1i out of here later
	m_locationSamplers[0] = glGetUniformLocation(getID(), "sampler");
	glUniform1i(m_locationSamplers[0], 0);
	m_locationSamplers[1] = glGetUniformLocation(getID(), "shadow");
	glUniform1i(m_locationSamplers[1], 1);
}
