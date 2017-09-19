#include "model.h"
#include "../Textures/texture.h"

Model::Buffer & Model::getBuffers()
{
	return m_buffers;
}

std::vector<Model::Buffer::iterator> & Model::getIdentifier()
{
	return identifier;
}

unsigned int & Model::getBufferCount()
{
	return m_vboCount;
}

GLuint & Model::getVAO()
{
	return m_vao;
}

unsigned int & Model::getPrimitiveCount()
{
	return primitiveCount;
}

Texture * Model::getTex()
{
	return texture;
}

void Model::setTex(Texture * texture)
{
	this->texture = texture;
}
