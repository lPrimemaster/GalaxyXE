#pragma once
#include "../common.h"

class Texture
{
public:
	//Delete copy and assignment ctors
	Texture(const Texture&) = delete;
	Texture &operator=(const Texture&) = delete;
	Texture &operator=(Texture &&tex);
	
	Texture(Texture&& tex);
	~Texture();

	const GLuint getTexture() const;

	void bind();
	void unbind();

	friend Texture loader::loadDDS(const std::string& filename);

private:
	Texture(GLuint texture);
	GLuint texture = 0;
	GLenum target;
};

