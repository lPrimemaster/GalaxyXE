#include "lighthandler.h"

#define CASE(Enum, Count, Type) \
case Enum: size = Count * sizeof(Type); break;

size_t TypeSize(GLenum type)
{

	size_t size;

	switch (type)
	{
		CASE(GL_FLOAT, 1, GLfloat);
		CASE(GL_FLOAT_VEC2, 2, GLfloat);
		CASE(GL_FLOAT_VEC3, 3, GLfloat);
		CASE(GL_FLOAT_VEC4, 4, GLfloat);

		CASE(GL_INT, 1, GLint);
		CASE(GL_INT_VEC2, 2, GLint);
		CASE(GL_INT_VEC3, 3, GLint);
		CASE(GL_INT_VEC4, 4, GLint);

		CASE(GL_UNSIGNED_INT, 1, GLuint);
		CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
		CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
		CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);

		CASE(GL_BOOL, 1, GLboolean);
		CASE(GL_BOOL_VEC2, 2, GLboolean);
		CASE(GL_BOOL_VEC3, 3, GLboolean);
		CASE(GL_BOOL_VEC4, 4, GLboolean);

		CASE(GL_FLOAT_MAT2, 4, GLfloat);
		CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
		CASE(GL_FLOAT_MAT2x4, 8, GLfloat);
		CASE(GL_FLOAT_MAT3, 9, GLfloat);
		CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
		CASE(GL_FLOAT_MAT3x4, 12, GLfloat);
		CASE(GL_FLOAT_MAT4, 16, GLfloat);
		CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
		CASE(GL_FLOAT_MAT4x3, 12, GLfloat);
	default:
		printf("[Typechecker] Unkown type: 0x%x\n", type);
		break;
	}
	return size;
}

const bool sendLightProperties(GLuint programID, const Light& light, std::string uniformBlockName, unsigned int index)
{
	Shader_Application_IO io(light);

	const char* names[12] = {
		"isEnabled",
		"lightType",
		"position",
		"direction",
		"color",
		"ambient",
		"coneDirection",
		"spotCosCutoff",
		"spotExponent",
		"constAtt",
		"linearAtt",
		"quadAtt"
	};

	const char _index = index + '0';
	GLuint cLoc[12];
	for (int i = 0; i < 12; i++)
	{
		const std::string fValue = uniformBlockName + "[" + _index + "]." + names[i];
		cLoc[i] = glGetUniformLocation(programID, fValue.c_str());
	}

	glUniform1i(cLoc[0], io.isEnabled);
	glUniform1ui(cLoc[1], io.lightType);
	glUniform3f(cLoc[2], io.position.x, io.position.y, io.position.z);
	glUniform3f(cLoc[3], io.direction.x, io.direction.y, io.direction.z);
	glUniform3f(cLoc[4], io.color.x, io.color.y, io.color.z);
	glUniform3f(cLoc[5], io.ambient.x, io.ambient.y, io.ambient.z);
	glUniform3f(cLoc[6], io.coneDirection.x, io.coneDirection.y, io.coneDirection.z);
	glUniform1f(cLoc[7], io.spotCosCutoff);
	glUniform1f(cLoc[8], io.spotExponent);
	glUniform1f(cLoc[9], io.constAtt);
	glUniform1f(cLoc[10], io.linearAtt);
	glUniform1f(cLoc[11], io.quadAtt);

	return true;
}
