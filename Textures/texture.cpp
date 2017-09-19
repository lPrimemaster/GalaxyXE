#include "texture.h"

Texture::Texture()
{
	target = GL_TEXTURE_2D;
}

Texture::Texture(GLenum target)
{
	this->target = target;
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::forceChannels(int channels)
{
	forcedChannels = channels;
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
