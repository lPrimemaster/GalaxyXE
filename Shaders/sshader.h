#pragma once
#include "program.h"

class SShader : public Program
{
public:
	SShader();
	SShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	virtual ~SShader() = default;

	void setProjViewMatrix(const vmath::mat4& matrix);
	void setModelMatrix(const vmath::mat4& matrix);

protected:
	virtual void getUniformLocations() override;

	GLuint m_locationProjViewMatrix = 0;
	GLuint m_locationModelMatrix = 0;
};

