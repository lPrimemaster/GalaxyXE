#include "loader.h"
#include <fstream>
#include <sstream>
#include "../Textures/texture.h"
#include "../Bitmap.h"
#include "../Utils/OBJparser/OBJparser.h"


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
	model.getTrueVertexCount() = vertices.size();
	loadEBO(indices, model);
	loadVBO(vertices, model, "VRT");
	loadVBO(uvs, model, "UVS");
	loadVBO(normals, model, "NRM");
	glBindVertexArray(0);
}

void Loader::loadRaw(Model & model, std::vector<glm::vec3> vertices)
{
	genVAO(model);
	model.modelType = GXE_ALT_MODEL;
	model.getVertexCount() = vertices.size();
	loadVBO(vertices, model, "VRT");
	glBindVertexArray(0);
}

void Loader::loadRaw(Model & model, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices)
{
	genVAO(model);
	model.modelType = GXE_DEFAULT_MODEL;
	model.getVertexCount() = vertices.size();
	loadEBO(indices, model);
	loadVBO(vertices, model, "VRT");
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

void Loader::loadShadowTexture(Texture & texture, GXE_Flags type)
{
	switch (type)
	{
	case GXE_ORTHOGONAL_MAP:
		loadOrthoMap(texture);
		break;
	case GXE_PERSPECTIVE_MAP:
		loadPerspMap(texture);
		break;
	case GXE_CUBE_PERSPECTIVE_MAP:
		loadCubePMap(texture);
		break;
	default: 
		break;
	}

	glBindTexture(texture.target, 0);

	if (glIsTexture(texture.getTexture()))
	{
		std::cout << "[Engine] Texture allocated successfully! ID [" << texture.getTexture() << "] for shadowMapping."  << std::endl;
	}
	else
	{
		std::cout << "[Engine] Failed to allocate texture for shadowMapping! " << std::endl;
	}
}

void Loader::loadTextureSB(Texture & texture, std::string halfPath)
{
	m_tex_path = "DATA/Textures/SkyBoxes/" + halfPath;

	Bitmap* map0 = new Bitmap(m_tex_path + "_rt.tga");
	Bitmap* map1 = new Bitmap(m_tex_path + "_lf.tga");
	Bitmap* map2 = new Bitmap(m_tex_path + "_up.tga");
	Bitmap* map3 = new Bitmap(m_tex_path + "_dn.tga");
	Bitmap* map4 = new Bitmap(m_tex_path + "_bk.tga");
	Bitmap* map5 = new Bitmap(m_tex_path + "_ft.tga");

	Bitmap* maps[6] = {map0, map1, map2, map3, map4, map5};

	texture.target = GL_TEXTURE_CUBE_MAP;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture.texture);
	glBindTexture(texture.target, texture.texture);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, maps[i]->getWidth(), maps[i]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (*maps[i])());
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	if (glIsTexture(texture.getTexture()))
	{
		std::cout << "[Engine] Texture loaded successfully! ID [" << texture.getTexture() << "] for skybox : " << m_tex_path << std::endl;
	}
	else
	{
		std::cout << "[Engine] Failed to load texture! -> " << m_tex_path << std::endl;
	}

	delete map0, map1, map2, map3, map4, map5;
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

void Loader::loadOrthoMap(Texture & texture)
{
	glActiveTexture(GL_TEXTURE1);
	texture.target = GL_TEXTURE_2D;
	glGenTextures(1, &texture.texture);
	glBindTexture(texture.target, texture.texture);

	glTexImage2D(texture.target, 0, GL_DEPTH_COMPONENT32, 1280, 720, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);


	float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glActiveTexture(GL_TEXTURE0);
}

void Loader::loadPerspMap(Texture & texture)
{
}

void Loader::loadCubePMap(Texture & texture)
{
}
