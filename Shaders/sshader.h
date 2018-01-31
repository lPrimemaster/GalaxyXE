#pragma once
#include "program.h"
#include "../Lights/light.h"

#define MAX_LIGHTS 10

class StaticShader : public Program
{
public:
	StaticShader();
	StaticShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	virtual ~StaticShader() = default;

	void setProjViewMatrix(const glm::mat4& matrix);
	void setModelMatrix(const glm::mat4& matrix);
	void setEyeDir(const glm::vec3& eyeDirection);

	void loadSampler(int unit, int texture);

	void setTime(float time);
	void setLight(Light* light);

protected:
	virtual void getUniformLocations() override;

	GLuint m_locationProjViewMatrix = 0;
	GLuint m_locationModelMatrix = 0;

	GLuint m_locationTime = 0;

	GLuint m_locationEyeDirection = 0;

	GLuint m_locationNumberLights = 0;
	GLuint m_locationLightProperties[12][MAX_LIGHTS] = { 0 };
};

