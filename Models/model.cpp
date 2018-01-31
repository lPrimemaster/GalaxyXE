#include "model.h"

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

unsigned int & Model::getVertexCount()
{
	return vertexCount;
}

