#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <map>

class Model
{
public:
	using Buffer = std::map<std::string, GLuint>;
	Model() = default;
	Buffer& getBuffers();
	std::vector<Buffer::iterator>& getIdentifier();
	unsigned int& getBufferCount();
	GLuint& getVAO();
	unsigned int& getVertexCount();

private:

	GLuint m_vao = 0;
	unsigned int m_vboCount = 0;
	unsigned int vertexCount = 0;
	std::vector<Buffer::iterator> identifier;
	Buffer m_buffers;

};

