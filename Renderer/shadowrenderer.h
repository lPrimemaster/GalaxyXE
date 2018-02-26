#pragma once
#include <iostream>
#include <map>
#include "renderer.h"
#include "../Shaders/shadowshader.h"
#include "../Textures/texture.h"
#include "../Lights/light.h"

class MasterRenderer;

class ShadowRenderer
{
public:
	ShadowRenderer();
	~ShadowRenderer();

	void update(MasterRenderer* renderer, Camera & cam);
	void draw(MasterRenderer * renderer);

private:
	ShadowShader m_shadowshader;
	StaticShader m_sshader2;
	std::map<Light*, Texture*> shadowMaps;
	Loader loader;
	glm::mat4 nMat;
	GLuint framebuffer;

	glm::mat4 biasMatrix;

};

