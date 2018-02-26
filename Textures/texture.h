#pragma once
#include "../common.h"
#include "../Models/loader.h"

class Texture
{
	friend class Loader;
	friend class ShadowShader;

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

