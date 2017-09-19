#pragma once
#include "renderer.h"

class MasterRenderer : public Renderer
{
public:
	MasterRenderer(const std::string & vertexShaderFile, const std::string & fragmentShaderFile);

	virtual void update(Camera& camera) override;
	virtual void draw() override;

	StaticShader* getShader();

private:
	StaticShader m_sshader;
	glm::mat4 t;

};

