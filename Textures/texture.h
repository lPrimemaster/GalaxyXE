#pragma once
#include "../common.h"

class Texture
{
public:
	Texture();
	Texture(GLenum target);
	~Texture();

	friend Texture * loader::loadTexture2D(std::string & filename);

	void forceChannels(int channels);
	const GLuint getTexture() const;

	void bind();
	void unbind();

private:
	GLuint texture;
	GLenum target;
	int width = 0, height = 0;
	int channels = 0, forcedChannels = 0; //extra params for sb_image loader lib [0 forced by default -> probably RGBA default]
};

