#pragma once
#include <string>
#include <stdexcept>
#include "model.h"
#include "../common.h"
#include "../Shaders/program.h"

class Texture;

///Vamp this class
class Loader
{
public:
	void loadFromObj(Model& model);
	void loadFromCollada(Model& model);
	void loadRaw(Model & model, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals);

	void loadtexture2D(Texture& texture);
	void setModInternalPath(const std::string name);
	void setTexInternalPath(const std::string name);

	void loadModel(Model& model, const std::string path);
	void loadTexture(Texture& texture, const std::string path);

private:
	std::string m_path;
	std::string m_tex_path;

	void loadEBO(const std::vector<unsigned int>& indices, Model& model);
	void loadVBO(const std::vector<glm::vec3>& data, Model& model, const std::string & identifier);
	void loadVBO(const std::vector<glm::vec2>& data, Model& model, const std::string & identifier);
	void genVAO(Model& model);
};

