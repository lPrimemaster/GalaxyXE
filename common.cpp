#include "common.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <map>
#include "Entities/entity.h"

std::string getSource(const std::string& sourceFile, const std::string& type)
{
	std::ifstream infile("DATA/Shaders/" + sourceFile + "." + type + ".glsl");
	std::string source;
	std::stringstream stringStream;

	if (!infile.is_open())
	{
		throw std::runtime_error("Couldn't open shader source: " + sourceFile);
	}

	stringStream << infile.rdbuf();
	source = stringStream.str();

	return source;
}

GLuint compileShader(const GLchar* source, GLenum type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	GLint status;
	GLchar infolog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infolog);
		throw std::runtime_error("Error compiling shader: " + std::string(infolog));
	}

	return shader;
}

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	GLint status;
	GLchar infolog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetProgramInfoLog(program, 512, nullptr, infolog);
		throw std::runtime_error("Error linking program: " + std::string(infolog));
	}

	return program;
}

GLuint loader::shaderLoader(const std::string& vertexShader, const std::string& fragmentShader)
{
	std::string vSource = getSource(vertexShader, "vert");
	std::string fSource = getSource(fragmentShader, "frag");

	GLuint vsID = compileShader(vSource.c_str(), GL_VERTEX_SHADER);
	GLuint fsID = compileShader(fSource.c_str(), GL_FRAGMENT_SHADER);

	GLuint programID = createProgram(vsID, fsID);

	glDeleteShader(vsID);
	glDeleteShader(fsID);

	return programID;
}

vmath::vec3 loader::parseVec3(const char * buffer)
{
	vmath::vec3 vector;
	sscanf(buffer, "%f %f %f", &vector[0], &vector[1], &vector[2]);
	return vector;
}

vmath::vec2 loader::parseVec2(const char * buffer)
{
	vmath::vec2 vector;
	sscanf(buffer, "%f %f", &vector[0], &vector[1]);
	return vector;
}

loader::DatasetGroup loader::parseFace(const char * buffer)
{
	DatasetGroup dataset;
	sscanf(buffer, "%u/%u/%u %u/%u/%u %u/%u/%u", &dataset.data[0].index, &dataset.data[0].temp_uv_ind, &dataset.data[0].temp_nm_ind,
												 &dataset.data[1].index, &dataset.data[1].temp_uv_ind, &dataset.data[1].temp_nm_ind,
												 &dataset.data[2].index, &dataset.data[2].temp_uv_ind, &dataset.data[2].temp_nm_ind);
	return dataset;
}

std::pair<Entity, std::string> initializer::makePair(Entity entity, std::string identifier)
{
	return std::make_pair(entity, identifier);
}
