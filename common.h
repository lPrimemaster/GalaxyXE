#pragma once
#include <iostream>
#include <GL/glew.h>
#include <string>
#include <vmath.h>

class Entity;

namespace loader
{
	GLuint shaderLoader(const std::string& vertexShader, const std::string& fragmentShader);
	vmath::vec3 parseVec3(const char* buffer);
	vmath::vec2 parseVec2(const char* buffer);
	
	typedef struct Dataset
	{
		unsigned int index;
		unsigned int temp_uv_ind;
		unsigned int temp_nm_ind;
	}Dataset;
	
	typedef struct DatasetGroup
	{
		Dataset data[3];
	}DatasetGroup;

	DatasetGroup parseFace(const char* buffer);
}

namespace initializer
{
	std::pair<Entity, std::string> makePair(Entity entity, std::string identifier);
}