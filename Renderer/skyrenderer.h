#pragma once
#include "../Shaders/skyshader.h"
#include "../Skybox/skybox.h"

class SkyRenderer
{
public:
	SkyRenderer();
	~SkyRenderer();

	void update(Camera& cam);
	void draw();

private:
	SkyShader m_skyshader;
	Skybox m_skybox;

};

