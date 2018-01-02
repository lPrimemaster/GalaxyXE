#include "texture.h"

Texture::~Texture()
{
	printf("[Debug] Texture destructor called!\n");
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

void Texture::build(GLuint texture)
{
	this->texture = texture;
}
