#pragma once
#include "program.h"
#include "../Lights/light.h"

class ShadowShader : public Program
{
public:
	ShadowShader();
	ShadowShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	~ShadowShader() = default;

	void setCurrentLight(Light* const light);
	void setModelMatrix(const glm::mat4& matrix);

protected:
	virtual void getUniformLocations() override;

private:
	Light * cLight;

	GLuint m_locationMVP;
};

