#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <map>

class Texture;

class Model
{
public:
	using Buffer = std::map<std::string, GLuint>;
	Model() = default;
	Buffer& getBuffers();
	std::vector<Buffer::iterator>& getIdentifier();
	unsigned int& getBufferCount();
	GLuint& getVAO();
	unsigned int& getPrimitiveCount();

	Texture* getTex();
	void setTex(Texture* texture);

protected:
	Texture* texture;

private:

	GLuint m_vao = 0;
	unsigned int m_vboCount = 0;
	unsigned int primitiveCount = 0;
	std::vector<Buffer::iterator> identifier;
	Buffer m_buffers;


};

