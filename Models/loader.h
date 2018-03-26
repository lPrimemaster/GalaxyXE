#pragma once
#include <string>
#include <stdexcept>
#include "model.h"
#include "../common.h"
#include "../Shaders/program.h"

class Texture;
typedef int GXE_Flags;

#define GXE_ORTHOGONAL_MAP 0x0C01
#define GXE_PERSPECTIVE_MAP 0x0C02
#define GXE_CUBE_PERSPECTIVE_MAP 0x0C03
#define GXE_SHADOW_RESOLUTION 1024

///Vamp this class
class Loader
{
public:
	void loadFromObj(Model& model);
	void loadFromCollada(Model& model);
	void loadRaw(Model & model, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals);
	void loadRaw(Model & model, std::vector<glm::vec3> vertices);
	void loadRaw(Model & model, std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);

	void loadtexture2D(Texture& texture);
	void setModInternalPath(const std::string name);
	void setTexInternalPath(const std::string name);

	void loadModel(Model& model, const std::string path);
	void loadTexture(Texture& texture, const std::string path);
	void loadShadowTexture(Texture& texture, GXE_Flags type);
	void loadTextureSB(Texture& texture, std::string halfPath);

private:
	std::string m_path;
	std::string m_tex_path;

	void loadEBO(const std::vector<unsigned int>& indices, Model& model);
	void loadVBO(const std::vector<glm::vec3>& data, Model& model, const std::string & identifier);
	void loadVBO(const std::vector<glm::vec2>& data, Model& model, const std::string & identifier);
	void genVAO(Model& model);

	void loadOrthoMap(Texture& texture);
	void loadPerspMap(Texture& texture);
	void loadCubePMap(Texture& texture);
};

