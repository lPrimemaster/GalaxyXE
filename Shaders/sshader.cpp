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
	static int i = 0; 
	if (light->ID() == -1)
		light->ID() = i++;
	int j = light->ID();
	loadInt(m_locationLightProperties[j][0], light->isEnabled());
	loadInt(m_locationLightProperties[j][1], light->getType());

	loadVector3f(m_locationLightProperties[j][2], light->getAmbient());
	loadVector3f(m_locationLightProperties[j][3], light->getColor());
	loadVector3f(m_locationLightProperties[j][4], light->getPosition());
	loadVector3f(m_locationLightProperties[j][5], light->getConeDirection());
	loadVector3f(m_locationLightProperties[j][6], light->getHalfVector());

	loadFloat(m_locationLightProperties[j][7], light->getSpotCosCutoff());
	loadFloat(m_locationLightProperties[j][8], light->getSpotExponent());
	loadFloat(m_locationLightProperties[j][9], light->getConstantAttenuation());
	loadFloat(m_locationLightProperties[j][10], light->getLinearAttenuation());
	loadFloat(m_locationLightProperties[j][11], light->getQuadraticAttenuation());

	light->mark();
}

void StaticShader::getUniformLocations()
{
	m_locationProjViewMatrix = glGetUniformLocation(getID(), "ProjView");
	m_locationModelMatrix = glGetUniformLocation(getID(), "Model");

	m_locationEyeDirection = glGetUniformLocation(getID(), "EyeDirection");

	m_locationTime = glGetUniformLocation(getID(), "t");

	std::string ftext;
	std::string init = "lights[";
	const char members[12][21] = {
		"isEnabled", "type", "ambient", "color", "position", "coneDirection", "halfVector", "spotCosCutoff", 
		"spotExponent", "constantAttenuation", "linearAttenuation", "quadraticAttenuation"
		};
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		char c = i + '0';
		ftext = init + c + "].";
		for(int j = 0; j < 12; j++)
			m_locationLightProperties[i][j] = glGetUniformLocation(getID(), (ftext + members[j]).c_str());
	}
}
