#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <map>
#define GXE_DEFAULT_MODEL 0
#define GXE_ALT_MODEL 1

#define GXE_MODEL_WIREFRAME 0
#define GXE_MODEL_RENDER_TYPE 1

#define GXE_OFF 0
#define GXE_ON  1

typedef int GXE_Flags;

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
	unsigned int& getTrueVertexCount();

	inline void attachParam(GXE_Flags param, GLenum value)
	{
		switch (param)
		{
		case GXE_MODEL_WIREFRAME:
			wireframe = value;
		case GXE_MODEL_RENDER_TYPE:
			renderType = value;
		default:
			break;
		}
	}

private:

	GLuint m_vao = 0;
	unsigned int m_vboCount = 0;
	unsigned int vertexCount = 0;
	unsigned int trueVertexCount = 0;
	std::vector<Buffer::iterator> identifier;
	Buffer m_buffers;

public:
	unsigned int modelType = GXE_DEFAULT_MODEL;
	GLenum wireframe = GXE_OFF;
	GLenum renderType = GL_TRIANGLES;

};

