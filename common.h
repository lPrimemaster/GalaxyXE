#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <fstream>
#include <cstdint>
#include <experimental/filesystem>

class Entity;

const unsigned int GXE_HARDWARE_THREAD_CONCURRENCY = std::thread::hardware_concurrency();

namespace loader
{
	GLuint shaderLoader(const std::string& vertexShader, const std::string& fragmentShader);

	glm::vec3 parseVec3(const char* buffer);
	glm::vec2 parseVec2(const char* buffer);

}

namespace common
{
	inline bool fileCheck(const std::experimental::filesystem::path& p)
	{
		if (std::experimental::filesystem::exists(p))
			return true;
		else
			return false;
	}
}

namespace collada
{
	class Float_Array
	{
		unsigned int m_count;
		std::string m_ID;
		float* m_floats;
	};

	class Name_Array
	{
		unsigned int m_count;
		std::string m_ID;
		std::string* m_floats;
	};

	class Param
	{
		std::string m_name;
		std::string m_type;
	};

	class Accessor
	{
		std::string m_source;
		unsigned int m_count;
		unsigned int m_stride;
		std::vector<Param> m_params;
	};

	class Technique_Common
	{
		Accessor m_accessor;
	};

	class Source
	{
		std::string m_ID;
		Float_Array m_float_array;
		Name_Array m_name_array;
		Technique_Common m_technique_common;
	};

	class Input
	{
		std::string m_semantic;
		std::string m_source;
		std::string m_offset;
		std::string m_set;
	};

	class Vertices
	{
		std::string m_ID;
		std::vector<Input> m_inputs;
	};

	class P
	{
		unsigned int m_count;
		unsigned short* m_indices;
	};

	class Triangles
	{
		unsigned int m_count;
		std::string m_material;
		std::vector<Input> m_inputs;
		P m_p;
	};

	class Mesh
	{
		unsigned int m_count;
		Vertices m_vertices;
		std::vector<Triangles> m_triangles;
	};

	class Geometry
	{
	private:
		Mesh m_mesh;
	};

	class GeometryLibrary
	{
	private:
		std::vector<Geometry> m_geometries;
	};

	class Collada
	{
	private:
		GeometryLibrary m_geomLib;
	};
}

namespace initializer
{
	std::pair<Entity, std::string> makePair(Entity entity, std::string identifier);
	bool createContext(GLFWwindow* window, glm::uvec2 resolution, const char* title);
	void checkContext(bool contextret);
}


