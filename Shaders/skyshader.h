#pragma once
#include "program.h"
class SkyShader : public Program
{
public:
	SkyShader();
	~SkyShader();

	void setProjViewMatrix(const glm::mat4& matrix);

protected:
	void getUniformLocations() override;

private:
	GLuint m_locationProjViewMatrix = 0;
};

