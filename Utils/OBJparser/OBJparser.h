#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <mutex>
#include "../XMLparser/stringutils.h"

#define GXE_OBJ_DATA 0x01
#define GXE_BIN_DATA_PARSE 0x0A
#define GXE_BIN_DATA_LOAD 0x064

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
	std::vector<glm::vec3> loadNRM();
	std::vector<unsigned int> loadIND();


private:
	inline glm::vec2 parseVec2(str::string string);
	inline glm::vec3 parseVec3(str::string string);
	inline void parseFace(std::vector<str::string> data, std::vector<unsigned int>& indices, glm::vec2* uvi, glm::vec3* nmi, std::vector<glm::vec2>& tuvs, std::vector<glm::vec3>& tnrm);
	inline void parseToBin(const std::string& path);
	inline void loadFromBin(const std::string& path);

private:
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
	return glm::vec2(atof(result[1]().c_str()), 1.0f - atof(result[2]().c_str()));
}

inline glm::vec3 OBJparser::parseVec3(str::string string)
{
	std::vector<str::string> result = string.split(" ");
	return glm::vec3(atof(result[1]().c_str()), atof(result[2]().c_str()), atof(result[3]().c_str()));
}

inline void OBJparser::parseFace(std::vector<str::string> data, std::vector<unsigned int>& indices, glm::vec2* uvi, glm::vec3* nmi, std::vector<glm::vec2>& tuvs, std::vector<glm::vec3>& tnrm)
{
	int vertexpointer = atoi(data[0]().c_str()) - 1;
	indices.push_back(vertexpointer);
	unsigned int uvpointer = atoi(data[1]().c_str()) - 1;
	uvi[vertexpointer] = glm::vec2(tuvs[uvpointer].x, tuvs[uvpointer].y);
	nmi[vertexpointer] = tnrm[atoi(data[2]().c_str()) - 1];
}

inline void OBJparser::parseToBin(const std::string& path)
{
	FILE* f = fopen(("DATA/Models/" + path + ".bin").c_str(), "wb");

	if (f == NULL)
	{
		std::cout << "[OBJparser] Failed to create bin file at: " << path << std::endl;
		return;
	}

	//Allocate all data in a binary buffer -> count size for HEADER

	struct
	{
		const unsigned int VERSION = 0x001;
		const char         EXTENSION[4] = "BIN";
		unsigned int offset[4];
	}HEADER;

	HEADER.offset[0] = vertices.size() * sizeof(glm::vec3);
	HEADER.offset[1] = indices.size() * sizeof(unsigned int);
	HEADER.offset[2] = normals.size() * sizeof(glm::vec3);
	HEADER.offset[3] = uvs.size() * sizeof(glm::vec2);

	unsigned int totalSize = sizeof(HEADER) + HEADER.offset[0] + HEADER.offset[1] + HEADER.offset[2] + HEADER.offset[3];

	unsigned char* packedData = (unsigned char*)malloc(totalSize);

	//Header info ready to write
	memcpy(packedData, reinterpret_cast<unsigned char*>(&HEADER), sizeof(HEADER));

	//Write vertices data into buffer - ready for write
	memcpy(packedData + sizeof(HEADER), reinterpret_cast<unsigned char*>(vertices.data()), HEADER.offset[0]);

	//Write indices data into buffer - ready for write
	memcpy(packedData + sizeof(HEADER) + HEADER.offset[0], reinterpret_cast<unsigned char*>(indices.data()), HEADER.offset[1]);

	//Write normals data into buffer - ready for write
	memcpy(packedData + sizeof(HEADER) + HEADER.offset[0] + HEADER.offset[1], reinterpret_cast<unsigned char*>(normals.data()), HEADER.offset[2]);

	//Write uvs data into buffer - ready for write
	memcpy(packedData + sizeof(HEADER) + HEADER.offset[0] + HEADER.offset[1] + HEADER.offset[2], reinterpret_cast<unsigned char*>(vertices.data()), HEADER.offset[3]);

	fwrite(packedData, totalSize, 1, f);

	free(packedData);

	fclose(f);
}

inline void OBJparser::loadFromBin(const std::string & path)
{
	
	FILE* f = fopen(("DATA/Models/" + path + ".bin").c_str(), "rb");

	struct
	{
		unsigned int VERSION;
		char         EXTENSION[4];
		unsigned int offset[4];
	}HEADER;

	fread(reinterpret_cast<unsigned char*>(&HEADER), sizeof(HEADER), 1, f);

	unsigned char* modelDataBuffer = (unsigned char*)malloc(HEADER.offset[0] + HEADER.offset[1] + HEADER.offset[2] + HEADER.offset[3]);

	fread(modelDataBuffer, HEADER.offset[0], 1, f);
	fread(modelDataBuffer + HEADER.offset[0], HEADER.offset[1], 1, f);
	fread(modelDataBuffer + HEADER.offset[0] + HEADER.offset[1], HEADER.offset[2], 1, f);
	fread(modelDataBuffer + HEADER.offset[0] + HEADER.offset[1] + HEADER.offset[2], HEADER.offset[3], 1, f);

	vertices.clear();
	vertices.reserve(HEADER.offset[0] / sizeof(glm::vec3));
	std::vector<glm::vec3> tvecV(reinterpret_cast<glm::vec3*>(modelDataBuffer), reinterpret_cast<glm::vec3*>(modelDataBuffer) + HEADER.offset[0] / sizeof(glm::vec3));
	vertices = tvecV;

	indices.clear();
	indices.reserve(HEADER.offset[1] / sizeof(unsigned int));
	std::vector<unsigned int> tvecI(reinterpret_cast<unsigned int*>(modelDataBuffer + HEADER.offset[0]), reinterpret_cast<unsigned int*>(modelDataBuffer + HEADER.offset[0]) + HEADER.offset[1] / sizeof(unsigned int));
	indices = tvecI;

	normals.clear();
	normals.reserve(HEADER.offset[2] / sizeof(glm::vec3));
	std::vector<glm::vec3> tvecN(reinterpret_cast<glm::vec3*>(modelDataBuffer + HEADER.offset[0] + HEADER.offset[1]), reinterpret_cast<glm::vec3*>(modelDataBuffer + HEADER.offset[0] + HEADER.offset[1]) + HEADER.offset[2] / sizeof(glm::vec3));
	normals = tvecN;

	uvs.clear();
	uvs.reserve(HEADER.offset[3] / sizeof(glm::vec2));
	std::vector<glm::vec2> tvecU(reinterpret_cast<glm::vec2*>(modelDataBuffer + HEADER.offset[0] + HEADER.offset[1] + HEADER.offset[2]), reinterpret_cast<glm::vec2*>(modelDataBuffer + HEADER.offset[0] + HEADER.offset[1] + HEADER.offset[2]) + HEADER.offset[3] / sizeof(glm::vec2));
	uvs = tvecU;

	free(modelDataBuffer);
}
