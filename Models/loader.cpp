#include "loader.h"
#include <fstream>
#include <sstream>
#include "../Textures/texture.h"
#include "../Bitmap.h"
#include "../Utils/OBJparser/OBJparser.h"

/* Erroring */
void Loader::loadFromObj(Model & model)
{
	time_t d0 = clock();
	if (m_path.empty())
	{
		throw std::runtime_error("[Loader] The specified object name can't be NULL.");
	}

	OBJparser p;

	p[m_path];
	try
	{
		p.read(GXE_BIN_DATA_PARSE | GXE_OBJ_DATA | GXE_BIN_DATA_LOAD);
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::vector<glm::vec3> vertices = p.loadVRT();
	std::vector<unsigned int> indices = p.loadIND();
	std::vector<glm::vec2> uvs = p.loadUVS();
	std::vector<glm::vec3> normals = p.loadNRM();

	loadRaw(model, vertices, indices, uvs, normals);
	std::cout << "[Engine] Model loaded successfully! " << "(" << (clock() - d0) << " clocks)" << " -> " << m_path << std::endl;
}


void Loader::loadFromCollada(Model & model)
{

}

void Loader::loadRaw(Model & model, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals)
{
	genVAO(model);
	model.getVertexCount() = indices.size();
	loadEBO(indices, model);
	loadVBO(vertices, model, "VRT");
	loadVBO(uvs, model, "UVS");
	loadVBO(normals, model, "NRM");
	glBindVertexArray(0);
}

void Loader::loadtexture2D(Texture& texture)
{
	if (m_tex_path.empty())
	{
		throw std::runtime_error("[Loader] The specified texture name can't be NULL.");
		return;
	}
	else
	{
		Bitmap* map = new Bitmap(m_tex_path);

		glGenTextures(1, &texture.texture);
		glBindTexture(GL_TEXTURE_2D, texture.texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (map->getChannels() == 3) //RGB
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, map->getWidth(), map->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, (*map)());
		}
		else if (map->getChannels() == 4) //RGBA
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, map->getWidth(), map->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (*map)());
		}
		else
		{
			throw std::runtime_error("[Loader] The specified bitmap internal configuration is unreadable.");
			return;
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		if (glIsTexture(texture.getTexture()))
		{
			std::cout << "[Engine] Texture loaded successfully! ID [" << texture.getTexture() << "] -> " << m_tex_path << std::endl;
		}
		else
		{
			std::cout << "[Engine] Failed to load texture! -> " << m_tex_path << std::endl;
		}

	}
}

void Loader::setModInternalPath(const std::string name)
{
	m_path = name;
}

void Loader::setTexInternalPath(const std::string name)
{
	m_tex_path = "DATA/Textures/" + name + ".tga";
}

void Loader::loadModel(Model & model, const std::string path)
{
	setModInternalPath(path);
	try
	{
		loadFromObj(model);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Loader::loadTexture(Texture & texture, const std::string path)
{
	setTexInternalPath(path);
	try
	{
		loadtexture2D(texture);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Loader::loadEBO(const std::vector<unsigned int> & indices, Model & model)
{
	GLuint elementbuffer[1];
	glGenBuffers(1, elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

	auto emplaced = model.getBuffers().emplace(std::string("EBO"), elementbuffer[0]);
	model.getIdentifier().push_back(emplaced.first);
}

void Loader::loadVBO(const std::vector<glm::vec3> & data, Model & model, const std::string & identifier)
{
	GLuint buffer[1];
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), &data.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(model.getBufferCount(), 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(model.getBufferCount()++);

	auto emplaced = model.getBuffers().emplace(std::string(identifier), buffer[0]);
	model.getIdentifier().push_back(emplaced.first);
}

void Loader::loadVBO(const std::vector<glm::vec2> & data, Model & model, const std::string & identifier)
{
	GLuint buffer[1];
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), &data.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(model.getBufferCount(), 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(model.getBufferCount()++);

	auto emplaced = model.getBuffers().emplace(std::string(identifier), buffer[0]);
	model.getIdentifier().push_back(emplaced.first);
}

void Loader::genVAO(Model & model)
{
	GLuint vao[1];
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	model.getVAO() = vao[0];
}
