#pragma once
#include "../common.h"
#include "../Models/loader.h"
#include "../Gui/gui.h"

class Texture
{
	friend class Loader;
	friend class ShadowShader;
	friend void Gui::associateTexture(const GLuint buffer);

public:
	Texture() = default;
	~Texture();

	const GLuint getTexture() const;

	void bind();
	void unbind();

private:
	void build(GLuint texture);

private:
	GLuint texture = 0;
	GLenum target = GL_TEXTURE_2D; //Using this by default
};

