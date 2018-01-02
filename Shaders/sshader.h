#pragma once
#include "program.h"

class StaticShader : public Program
{
public:
	StaticShader();
	StaticShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	virtual ~StaticShader() = default;

	void setProjViewMatrix(const glm::mat4& matrix);
	void setModelMatrix(const glm::mat4& matrix);

	void loadSampler(int unit, int texture);

	void setTime(float time);

protected:
	virtual void getUniformLocations() override;

	GLuint m_locationProjViewMatrix = 0;
	GLuint m_locationModelMatrix = 0;
	GLuint m_locationTime = 0;
};

