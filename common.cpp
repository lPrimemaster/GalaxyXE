#include "common.h"

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <map>
#include "Entities/entity.h"
#include "Textures/texture.h"

#define GXE_FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define GXE_FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define GXE_FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

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

Texture loader::loadDDS(const std::string & filename)
{
	unsigned char header[124];

	FILE *fp = fopen(filename.c_str(), "rb");
	if (fp == NULL)
	{
		throw std::runtime_error("[Engine] File path for texture loading not available.");
		return Texture(0);
	}

	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0)
	{
		fclose(fp);
		throw std::runtime_error("[Engine] File is not DDS.");
		return Texture(0);
	}

	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);
	
	/* Read all the data */

	unsigned char* buffer;
	unsigned int buffSize;

	buffSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(buffSize * sizeof(unsigned char));
	fread(buffer, 1, buffSize, fp);

	fclose(fp);

	unsigned int components = (fourCC == GXE_FOURCC_DXT1) ? 3 : 4;
	unsigned int format;

	switch (fourCC)
	{
		case GXE_FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case GXE_FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case GXE_FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
		default:
			free(buffer);
			throw std::runtime_error("[Engine] Invalid texture compression format.");
			return Texture(0);
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	for (int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

		offset += size;

		width /= 2;
		height /= 2;
	}

	free(buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (glIsTexture(textureID))
	{
		std::cout << "[Engine] Texture loaded successfully!" << std::endl;
	}

	return Texture(textureID);
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

