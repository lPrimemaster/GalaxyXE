#pragma once
#include <iostream>
#include <map>
#include "renderer.h"
#include "../Shaders/shadowshader.h"
#include "../Textures/texture.h"
#include "../Lights/light.h"
#include "../Lights/shadowbox.h"
#include "../Gui/gui.h"

class MasterRenderer;

class ShadowRenderer
{
public:
	ShadowRenderer();
	~ShadowRenderer();

	void update(MasterRenderer* renderer, Camera & cam);
	void draw(MasterRenderer * renderer);
	std::map<Light*, Texture*>& getShadowMaps();

private:
	ShadowShader m_shadowshader;
	std::map<Light*, Texture*> shadowMaps;
	Loader loader;
	glm::mat4 nMat;
	GLuint framebuffer;

	Gui gui;

	glm::mat4 biasMatrix;

};

