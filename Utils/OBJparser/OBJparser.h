#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <mutex>
#include "../XMLparser/stringutils.h"
#include "../LinkedVertex/lvertex.h"

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
	inline int dealDuplicate(LinkedVertex* last, unsigned int newuvPointer, unsigned int newnPointer, glm::vec2** uvi, glm::vec3** nmi);

private:
	std::string path;
	std::vector<str::string> data;

	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

private:
	std::vector<LinkedVertex> vList;
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

inline int OBJparser::dealDuplicate(LinkedVertex * last, unsigned int newuvPointer, unsigned int newnPointer, glm::vec2** uvi, glm::vec3** nmi)
{
	if (last->checkPointers(newuvPointer, newnPointer))
	{
		indices.push_back(last->getvPointer());
		return last->getvPointer();
	}
	else
	{
		LinkedVertex* newVertex = last->getDuplicate();
		if (newVertex != NULL)
		{
			dealDuplicate(newVertex, newuvPointer, newnPointer, uvi, nmi);
		}
		else
		{
			static const int offset = 1;
			static size_t arraylenght = vertices.size();
			*uvi = (glm::vec2*)realloc(*uvi, (arraylenght + offset) * sizeof(glm::vec2));
			*nmi = (glm::vec3*)realloc(*nmi, (arraylenght + offset) * sizeof(glm::vec3));
			arraylenght += offset;
			LinkedVertex* duplicate = new LinkedVertex(vertices.size(), last->getPosition());
			duplicate->setTextureIndex(newuvPointer);
			duplicate->setNormalIndex(newnPointer);
			last->setDuplicate(duplicate);
			indices.push_back(vertices.size());
			vertices.push_back(duplicate->getPosition());
			return duplicate->getvPointer();
		}
	}
}

inline void OBJparser::parseFace(std::vector<str::string> data, std::vector<unsigned int>& indices, glm::vec2* uvi, glm::vec3* nmi, std::vector<glm::vec2>& tuvs, std::vector<glm::vec3>& tnrm)
{
	unsigned int assignValue = vertices.size();
	int vertexpointer = atoi(data[0]().c_str()) - 1;
	LinkedVertex currentVertex = vList[vertexpointer];
	unsigned int uvPointer = atoi(data[1]().c_str()) - 1;
	unsigned int nPointer = atoi(data[2]().c_str()) - 1;
	if (!currentVertex.isSet())
	{
		currentVertex.setNormalIndex(nPointer);
		currentVertex.setTextureIndex(uvPointer);
		indices.push_back(vertexpointer);
	}
	else
	{
		vertexpointer = dealDuplicate(&currentVertex, uvPointer, nPointer, &uvi, &nmi);
	}
	uvi[vertexpointer] = glm::vec2(tuvs[uvPointer].x, tuvs[uvPointer].y);
	nmi[vertexpointer] = tnrm[nPointer];
}

inline void OBJparser::parseToBin(const std::string& path)
{
	FILE* f = fopen(("DATA/Models/" + path + ".bin").c_str(), "wb");

	if (f == NULL)
	{
		std::cout << "[OBJparser] Failed to create bin file at: " << "DATA/Models/" + path + ".bin" << std::endl;
		return;
	}

	//Allocate all data in a binary buffer -> count size for HEADER

	struct
	{
		const unsigned int VERSION = 0x001;
		const char         EXTENSION[4] = "BIN";
		unsigned int       OFFSET[4];
	}HEADER;

	HEADER.OFFSET[0] = vertices.size() * sizeof(glm::vec3);
	HEADER.OFFSET[1] = indices.size() * sizeof(unsigned int);
	HEADER.OFFSET[2] = normals.size() * sizeof(glm::vec3);
	HEADER.OFFSET[3] = uvs.size() * sizeof(glm::vec2);

	unsigned int totalSize = sizeof(HEADER) + HEADER.OFFSET[0] + HEADER.OFFSET[1] + HEADER.OFFSET[2] + HEADER.OFFSET[3];

	unsigned char* packedData = (unsigned char*)malloc(totalSize);

	//Header info ready to write
	memcpy(packedData, reinterpret_cast<unsigned char*>(&HEADER), sizeof(HEADER));

	//Write vertices data into buffer - ready for write
	memcpy(packedData + sizeof(HEADER), reinterpret_cast<unsigned char*>(vertices.data()), HEADER.OFFSET[0]);

	//Write indices data into buffer - ready for write
	memcpy(packedData + sizeof(HEADER) + HEADER.OFFSET[0], reinterpret_cast<unsigned char*>(indices.data()), HEADER.OFFSET[1]);

	//Write normals data into buffer - ready for write
	memcpy(packedData + sizeof(HEADER) + HEADER.OFFSET[0] + HEADER.OFFSET[1], reinterpret_cast<unsigned char*>(normals.data()), HEADER.OFFSET[2]);

	//Write uvs data into buffer - ready for write
	memcpy(packedData + sizeof(HEADER) + HEADER.OFFSET[0] + HEADER.OFFSET[1] + HEADER.OFFSET[2], reinterpret_cast<unsigned char*>(uvs.data()), HEADER.OFFSET[3]);

	fwrite(packedData, totalSize, 1, f);

	free(packedData);

	fclose(f);
}

inline void OBJparser::loadFromBin(const std::string & path)
{
	
	FILE* f = fopen(("DATA/Models/" + path + ".bin").c_str(), "rb");

	if (f == NULL)
	{
		std::cout << "[OBJparser] Failed to read bin file at: " << "DATA/Models/" + path + ".bin" << std::endl;
		return;
	}

	struct
	{
		unsigned int VERSION;
		char         EXTENSION[4];
		unsigned int OFFSET[4];
	}HEADER;

	fread(reinterpret_cast<unsigned char*>(&HEADER), sizeof(HEADER), 1, f);

	unsigned char* modelDataBuffer = (unsigned char*)malloc(HEADER.OFFSET[0] + HEADER.OFFSET[1] + HEADER.OFFSET[2] + HEADER.OFFSET[3]);

	fread(modelDataBuffer, HEADER.OFFSET[0], 1, f);
	fread(modelDataBuffer + HEADER.OFFSET[0], HEADER.OFFSET[1], 1, f);
	fread(modelDataBuffer + HEADER.OFFSET[0] + HEADER.OFFSET[1], HEADER.OFFSET[2], 1, f);
	fread(modelDataBuffer + HEADER.OFFSET[0] + HEADER.OFFSET[1] + HEADER.OFFSET[2], HEADER.OFFSET[3], 1, f);

	vertices.clear();
	vertices.reserve(HEADER.OFFSET[0] / sizeof(glm::vec3));
	std::vector<glm::vec3> tvecV(reinterpret_cast<glm::vec3*>(modelDataBuffer), reinterpret_cast<glm::vec3*>(modelDataBuffer) + HEADER.OFFSET[0] / sizeof(glm::vec3));
	vertices = tvecV;

	indices.clear();
	indices.reserve(HEADER.OFFSET[1] / sizeof(unsigned int));
	std::vector<unsigned int> tvecI(reinterpret_cast<unsigned int*>(modelDataBuffer + HEADER.OFFSET[0]), reinterpret_cast<unsigned int*>(modelDataBuffer + HEADER.OFFSET[0]) + HEADER.OFFSET[1] / sizeof(unsigned int));
	indices = tvecI;

	normals.clear();
	normals.reserve(HEADER.OFFSET[2] / sizeof(glm::vec3));
	std::vector<glm::vec3> tvecN(reinterpret_cast<glm::vec3*>(modelDataBuffer + HEADER.OFFSET[0] + HEADER.OFFSET[1]), reinterpret_cast<glm::vec3*>(modelDataBuffer + HEADER.OFFSET[0] + HEADER.OFFSET[1]) + HEADER.OFFSET[2] / sizeof(glm::vec3));
	normals = tvecN;

	uvs.clear();
	uvs.reserve(HEADER.OFFSET[3] / sizeof(glm::vec2));
	std::vector<glm::vec2> tvecU(reinterpret_cast<glm::vec2*>(modelDataBuffer + HEADER.OFFSET[0] + HEADER.OFFSET[1] + HEADER.OFFSET[2]), reinterpret_cast<glm::vec2*>(modelDataBuffer + HEADER.OFFSET[0] + HEADER.OFFSET[1] + HEADER.OFFSET[2]) + HEADER.OFFSET[3] / sizeof(glm::vec2));
	uvs = tvecU;

	free(modelDataBuffer);
}
