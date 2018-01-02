#include "common.h"

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <map>
#include "Entities/entity.h"
#include "Textures/texture.h"

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
	std::string vSource, fSource;
	try 
	{
		vSource = getSource(vertexShader, "vert");
		fSource = getSource(fragmentShader, "frag");
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}

	GLuint vsID, fsID;
	try
	{
		vsID = compileShader(vSource.c_str(), GL_VERTEX_SHADER);
		fsID = compileShader(fSource.c_str(), GL_FRAGMENT_SHADER);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	GLuint programID;
	try
	{
		programID = createProgram(vsID, fsID);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}

	glDeleteShader(vsID);
	glDeleteShader(fsID);

	return programID;
}

glm::vec3 loader::parseVec3(const char * buffer)
{
	glm::vec3 vector;
	sscanf(buffer, "%f %f %f", &vector[0], &vector[1], &vector[2]);
	return vector;
}

glm::vec2 loader::parseVec2(const char * buffer)
{
	glm::vec2 vector;
	sscanf(buffer, "%f %f", &vector[0], &vector[1]);
	return vector;
}

std::pair<Entity, std::string> initializer::makePair(Entity entity, std::string identifier)
{
	return std::make_pair(entity, identifier);
}

bool initializer::createContext(GLFWwindow* window, glm::uvec2 resolution, const char* title)
{
	//GLFW3 INIT
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	//Dummy context
	window = glfwCreateWindow(resolution[0], resolution[1], title, NULL, NULL);
	glfwMakeContextCurrent(window);

	//GLEW INIT
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "[Engine] Glew failed to initialize with error: " << (char*)glewGetErrorString(err) << std::endl;
		return false;
	}
	else
	{
		std::cout << "[Engine] Glew initialized! Using version: " << glewGetString(GLEW_VERSION) << std::endl;
		return true;
	}
}


/* Deprecated */
void initializer::checkContext(bool contextret)
{
	if (!contextret)
	{
		std::cout << "[CheckerThread] Glew state flagged as incorrect! Terminating program!" << std::endl;
		exit(0x3E8);
	}
	else
	{
		std::cout << "[CheckerThread] Glew state flagged as correct! Procceding to mainthread!" << std::endl;
		putchar('\n');
	}
}

