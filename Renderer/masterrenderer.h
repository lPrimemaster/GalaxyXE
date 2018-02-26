#pragma once
#include "renderer.h"
#include "shadowrenderer.h"

class MasterRenderer : public Renderer
{
public:
	friend class ShadowRenderer;
	MasterRenderer(const std::string & vertexShaderFile, const std::string & fragmentShaderFile);

	virtual void update(Camera& camera) override;
	virtual void draw() override;


private:
	StaticShader m_sshader;
	ShadowRenderer m_shadowrenderer;
};

