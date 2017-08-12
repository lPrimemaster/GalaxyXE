#pragma once
#include <string>
#include <stdexcept>
#include "model.h"
#include "../common.h"

class Loader
{
public:
	void loadFromObj(Model& model);
	void setInternalPath(const std::string name);

private:
	std::string m_path;

	void loadEBO(const std::vector<unsigned int>& indices, Model& model);
	void loadVBO(const std::vector<vmath::vec3>& data, Model& model);
	void loadVBO(const std::vector<vmath::vec2>& data, Model& model);
	void genVAO(Model& model);
};

