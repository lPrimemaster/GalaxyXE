#include "shader.h"

Shader::Shader(GLenum type, const char * path)
{
	shader = glCreateShader(type);

	this->type = type;

	const GLchar* source = readFile(path);
	this->path = path;

	if (source == NULL)
	{
		std::cout << "Error loading shader! Source file is invalid or non existent." << std::endl;
		glDeleteShader(shader);
		shader = 0;
	}
	else
	{
		glShaderSource(shader, 1, &source, NULL);
		delete[] source;
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		std::cout << "Compile status for shader " << path << ": / ";
		if (!status)
		{
			std::cout << "ERRORED" << std::endl;

			//Show log with error
			GLint len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			std::cout << log << std::endl;
			delete log;

			glDeleteShader(shader);
			shader = 0;
		}
		else
		{
			std::cout << "COMPILED" << std::endl;
		}
	}
}

Shader::~Shader()
{
	glDeleteShader(shader);
}

void Shader::link(Program p)
{
	glAttachShader(p.getProgram(), shader);
	programID = p.getProgram();
}

GLuint & Shader::getProgram()
{
	return programID;
}

GLenum Shader::getType()
{
	return type;
}


const GLchar * Shader::readFile(const char* path)
{
	//Opening file
	FILE* source;
	fopen_s(&source, path, "rb");

	if (source == NULL)
	{
		std::cout << "Error reading shader source file:" << path << std::endl;
	}

	fseek(source, 0, SEEK_END);
	int len = ftell(source);
	fseek(source, 0, SEEK_SET);

	GLchar* buffer = new GLchar[len + 1];
	fread(buffer, 1, len, source);
	fclose(source);

	buffer[len] = 0;

	return const_cast<const GLchar*>(buffer);
}
