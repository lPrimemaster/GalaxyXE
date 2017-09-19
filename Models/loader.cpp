#include "loader.h"
#include <fstream>
#include <sstream>
#include "../Textures/texture.h"


void Loader::loadFromObj(Model & model)
{
	if (m_path.empty())
	{
		throw std::runtime_error("[Loader] The specified object name can't be NULL.");
	}
	FILE* f = fopen(m_path.c_str(), "r");

	if (f == nullptr)
	{
		throw std::runtime_error("[Loader] Couldn't open source file: " + m_path);
	}

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	unsigned int pCount = 0;
	unsigned int line_number = 0;

	std::vector<glm::vec3> temp_normals;
	std::vector<glm::vec2> temp_uvs;

	char p[128];

	while(fgets(p, 128, f) != nullptr)
	{
		line_number++;
		switch (p[0])
		{
			case '#': case 's': case 'u': case 'm': case 'o': case 'l': break;
			case 'v':
				switch (p[1])
				{
					case ' ':
						 vertices.push_back(loader::parseVec3(&p[2]));
						break;
					case 't':
						temp_uvs.push_back(loader::parseVec2(&p[3]));
						break;
					case 'n':
						temp_normals.push_back(loader::parseVec3(&p[3]));
						break;
				}
				break;
			case 'f':
				unsigned int index[3], uv_ind[3], nm_ind[3];
				sscanf(&p[2], "%d/%d/%d %d/%d/%d %d/%d/%d", &index[0], &uv_ind[0], &nm_ind[0],
															&index[1], &uv_ind[1], &nm_ind[1],
															&index[2], &uv_ind[2], &nm_ind[2]);
				try
				{
					indices.push_back(index[0] - 1);
					indices.push_back(index[1] - 1);
					indices.push_back(index[2] - 1);

					uvs.push_back(temp_uvs.at(uv_ind[0] - 1));
					uvs.push_back(temp_uvs.at(uv_ind[1] - 1));
					uvs.push_back(temp_uvs.at(uv_ind[2] - 1));

					normals.push_back(temp_normals.at(nm_ind[0] - 1));
					normals.push_back(temp_normals.at(nm_ind[1] - 1));
					normals.push_back(temp_normals.at(nm_ind[2] - 1));
				}
				catch(std::exception& e)
				{
					std::cout << "[Loader] Error [at LINE " << line_number << "]: " << e.what() << std::endl;
					exit(-1);
				}

				pCount++;
				break;
			default:
				throw std::runtime_error("[Loader] Uknown format caught from obj file: " + m_path + "::" + p[0]);
				break;
		}
	}

	program->bind();
	model.getPrimitiveCount() = pCount;
	genVAO(model);
	loadEBO(indices, model);
	loadVBO(vertices, model, "VRT"); //Atr 0
	loadVBO(uvs, model, "UVS"); //Atr 1
	//Loading normals in the future [?]
	
	program->unbind();

	std::cout << "[Loader] Successfully loaded model from path: " << m_path << std::endl;
}

void Loader::loadtexture2D(Model& model)
{
	if (m_tex_path.empty())
	{
		throw std::runtime_error("[Loader] The specified object name can't be NULL.");
	}

	//glUniform1i(glGetUniformLocation(program->getID(), "sampler"), 0); ///Active GL_TEXTURE0
	try
	{
		program->bind();
		model.setTex(loader::loadTexture2D(m_tex_path));
		program->unbind();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	if (!glIsTexture(model.getTex()->getTexture()))
		throw std::runtime_error("[Loader] No texture was provided to model"); ///Change this please
	else
		std::cout << "[Loader] Texture loading nominal" << std::endl;
}

void Loader::setInternalPath(const std::string name)
{
	m_path = "DATA/Objects/" + name + ".obj";
	m_tex_path = "DATA/Textures/" + name + ".jpg";
}

void Loader::setAttributeShader(Program * shader)
{
	this->program = shader;
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
