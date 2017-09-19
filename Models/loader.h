#pragma once
#include <string>
#include <stdexcept>
#include "model.h"
#include "../common.h"
#include "../Shaders/program.h"

class Loader
{
public:
	void loadFromObj(Model& model);
	void loadtexture2D(Model& model);
	void setInternalPath(const std::string name);
	void setAttributeShader(Program* shader);

private:
	std::string m_path;
	std::string m_tex_path;
	Program* program;

	void loadEBO(const std::vector<unsigned int>& indices, Model& model);
	void loadVBO(const std::vector<glm::vec3>& data, Model& model, const std::string & identifier);
	void loadVBO(const std::vector<glm::vec2>& data, Model& model, const std::string & identifier);
	void genVAO(Model& model);
};

