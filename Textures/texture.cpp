#include "texture.h"

Texture & Texture::operator=(Texture && tex)
{
	if (this != &tex)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
		std::swap(texture, tex.texture);
	}
	return *this;
}

Texture::Texture(Texture&& tex) : texture(tex.texture)
{
	tex.texture = 0;
}

Texture::Texture(GLuint texture)
{
	this->texture = texture;
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

const GLuint Texture::getTexture() const
{
	return texture;
}

void Texture::bind()
{
	glBindTexture(target, texture);
}

void Texture::unbind()
{
	glBindTexture(target, 0);
}
