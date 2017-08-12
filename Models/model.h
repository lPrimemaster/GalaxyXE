#pragma once
#include <vector>
#include <vmath.h>
#include <GL/glew.h>
#include <map>

class Model
{
public:
	using Buffer = std::map<GLuint, std::string>;
	Model() = default;
	Buffer& getBuffers();
	std::vector<Buffer::iterator>& getIdentifier();
	unsigned int& getBufferCount();
	GLuint& getVAO();

private:
	/// [WAS] Being used as a temp buffer
	//std::vector<vmath::vec3> m_vertices;
	//std::vector<unsigned int> m_indices;
	//std::vector<vmath::vec2> m_uvs;
	//std::vector<vmath::vec3> m_normals;

	GLuint m_vao = 0;
	unsigned int m_vboCount = 0;
	std::vector<Buffer::iterator> identifier;
	Buffer m_buffers;

};

