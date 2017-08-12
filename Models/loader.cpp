#include "loader.h"
#include <fstream>
#include <sstream>


void Loader::loadFromObj(Model & model)
{
	if (m_path.empty())
	{
		throw std::runtime_error("[Loader] The specified object name can't be NULL.");
	}
	FILE* f = fopen(m_path.c_str(), "r");

	if (f == nullptr)
	{
		throw std::runtime_error("Couldn't open source file: " + m_path);
	}

	std::vector<vmath::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<vmath::vec2> uvs;
	std::vector<vmath::vec3> normals;

	std::vector<vmath::vec3> temp_normals;
	std::vector<vmath::vec2> temp_uvs;
	std::vector<loader::Dataset> temp_data;

	char p[128];

	while(fgets(p, 128, f) != nullptr)
	{
		switch (p[0])
		{
			case '#': case 's': case 'u': case 'm': break;
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
				loader::DatasetGroup tds;
				tds = loader::parseFace(&p[2]);
				temp_data.push_back(tds.data[0]);
				temp_data.push_back(tds.data[1]);
				temp_data.push_back(tds.data[2]);
				break;
			default:
				throw std::runtime_error("Uknown format caught from obj file: " + m_path);
				break;
		}
	}

	for (unsigned int i = 0; i < temp_data.size(); i++)
	{
		indices.push_back(temp_data.at(i).index - 1); //-1 since obj files define starting index to be at 1
		uvs.push_back(temp_uvs.at(temp_data.at(i).temp_uv_ind - 1));
		normals.push_back(temp_normals.at(temp_data.at(i).temp_nm_ind - 1));
	}

	genVAO(model);
	loadEBO(indices, model);
	loadVBO(vertices, model);
	loadVBO(uvs, model);
	//Loading normals in the future [?]
	

	std::cout << "Successfully loaded model from path: " << m_path << std::endl;
}

void Loader::setInternalPath(const std::string name)
{
	m_path = "DATA/Objects/" + name + ".obj";
}

void Loader::loadEBO(const std::vector<unsigned int> & indices, Model & model)
{
	GLuint elementbuffer[1];
	glGenBuffers(1, elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);

	auto emplaced = model.getBuffers().emplace(elementbuffer[0], std::string("EBO"));
	model.getIdentifier().push_back(emplaced.first);
}

void Loader::loadVBO(const std::vector<vmath::vec3> & data, Model & model)
{
	GLuint buffer[1];
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(vmath::vec3), &data.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(model.getBufferCount(), 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(model.getBufferCount()++);

	auto emplaced = model.getBuffers().emplace(buffer[0], std::string("VBO"));
	model.getIdentifier().push_back(emplaced.first);
}

void Loader::loadVBO(const std::vector<vmath::vec2> & data, Model & model)
{
	GLuint buffer[1];
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(vmath::vec2), &data.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(model.getBufferCount(), 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(model.getBufferCount()++);

	auto emplaced = model.getBuffers().emplace(buffer[0], std::string("VBO"));
	model.getIdentifier().push_back(emplaced.first);
}

void Loader::genVAO(Model & model)
{
	GLuint vao[1];
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	model.getVAO() = vao[0];
}
