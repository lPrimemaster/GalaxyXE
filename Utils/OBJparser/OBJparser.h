#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include "../XMLparser/stringutils.h"

#define GXE_OBJ_NO_TEXTURES 0x0EF3
#define GXE_OBJ_NO_OBJECTS 0x0EF4
#define GXE_OBJ_NO_MATERIALS 0x0EF5

#define GXE_VRT 0x0EF7
#define GXE_UVS 0x0EF8
#define GXE_IND 0x0EF9

/*
* @SPECIFIERS
* GXE_OBJ_NO_TEXTURES -> No texture UV's in wavefront file
* GXE_OBJ_NO_OBJECTS -> Only one solid object exported / ignore them
* GXE_OBJ_NO_MATERIALS -> No materials exported trought wavefront file / ignore them
* @DATA
* GXE_VRT -> reference to vertex data vector of model
* GXE_UVS -> reference to uv coordinates data vector of model
* GXE_IND -> reference to elements order of model faces
*/
typedef int GXE_Flags;

class OBJparser
{
public:
	OBJparser();
	~OBJparser();

	void operator[](std::string path)
	{
		this->path = path;
	}

	void read(GXE_Flags flags);

	std::vector<glm::vec3> loadVRT();
	std::vector<glm::vec2> loadUVS();
	std::vector<unsigned int> loadIND();


private:
	inline glm::vec2 parseVec2(str::string string);
	inline glm::vec3 parseVec3(str::string string);
	inline void parseFace(str::string string, std::vector<unsigned int>& indices, std::vector<unsigned int>& uvs_ind, std::vector<unsigned int>& nrm_ind);

private:
	FILE* f;
	std::string path;
	std::vector<str::string> data;

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
};


inline glm::vec2 OBJparser::parseVec2(str::string string)
{
	std::vector<str::string> result = string.split(" ");
	return glm::vec2(atof(result[1]().c_str()), atof(result[2]().c_str()));
}

inline glm::vec3 OBJparser::parseVec3(str::string string)
{
	std::vector<str::string> result = string.split(" ");
	return glm::vec3(atof(result[1]().c_str()), atof(result[2]().c_str()), atof(result[3]().c_str()));
}

inline void OBJparser::parseFace(str::string string, std::vector<unsigned int>& indices, std::vector<unsigned int>& uvs_ind, std::vector<unsigned int>& nrm_ind)
{
	std::vector<str::string> result = string.split(" ");
	std::vector<str::string> face1 = result[1].split("/");
	std::vector<str::string> face2 = result[2].split("/");
	std::vector<str::string> face3 = result[3].split("/");

	indices.push_back(atoi(face1[0]().c_str()) - 1);
	indices.push_back(atoi(face2[0]().c_str()) - 1);
	indices.push_back(atoi(face3[0]().c_str()) - 1);

	uvs_ind.push_back(atoi(face1[1]().c_str()) - 1);
	uvs_ind.push_back(atoi(face2[1]().c_str()) - 1);
	uvs_ind.push_back(atoi(face3[1]().c_str()) - 1);

	nrm_ind.push_back(atoi(face1[2]().c_str()) - 1);
	nrm_ind.push_back(atoi(face2[2]().c_str()) - 1);
	nrm_ind.push_back(atoi(face3[2]().c_str()) - 1);
}
