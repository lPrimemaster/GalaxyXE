#pragma once
#include "../common.h"

class Program
{
public:
	Program(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	virtual ~Program();

	void bind();
	void unbind();

protected:
	virtual void getUniformLocations() = 0;

	GLuint getID() const;

	void loadInt(GLuint location, int& value);
	void loadFloat(GLuint location, float& value);
	void loadVector2f(GLuint location, const vmath::vec2& vector);
	void loadVector3f(GLuint location, const vmath::vec3& vector);
	void loadMatrix4f(GLuint location, const vmath::mat4& matrix);

private:
	GLuint m_programID;
};

