#pragma once
#include "program.h"
#include "../Lights/light.h"
#include "../Lights/dlight.h"
#include "../Lights/lighthandler.h"

class StaticShader : public Program
{
public:
	StaticShader();
	StaticShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	virtual ~StaticShader() = default;

	void setProjViewMatrix(const glm::mat4& matrix);
	void setModelMatrix(const glm::mat4& matrix);
	void setEyeDir(const glm::vec3& eyeDirection);
	void setDepthBiasMatrix(const glm::mat4& matrix);

	void loadSampler(int unit, int texture);

	void setTime(float time);
	void setLight(Light* light);

protected:
	virtual void getUniformLocations() override;

	GLuint m_locationProjViewMatrix = 0;
	GLuint m_locationModelMatrix = 0;

	GLuint m_locationTime = 0;

	GLuint m_locationDepthBiasMatrix = 0;

	GLuint m_locationEyeDirection = 0;

	GLuint m_locationNumberLights = 0;
	GLuint m_locationLightProperties[GXE_MAX_LIGHTS][12] = { 0 };
};

