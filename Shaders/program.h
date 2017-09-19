#pragma once
#include "../common.h"

class Program
{
public:
	Program(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	virtual ~Program();

	void bind();
	void unbind();
	GLuint getID() const;

protected:
	virtual void getUniformLocations() = 0;


	void loadInt(GLuint location, int& value);
	void loadFloat(GLuint location, float& value);
	void loadVector2f(GLuint location, const glm::vec2& vector);
	void loadVector3f(GLuint location, const glm::vec3& vector);
	void loadMatrix4f(GLuint location, const glm::mat4& matrix);

private:
	GLuint m_programID;
};

