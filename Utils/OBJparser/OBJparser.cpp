#include "OBJparser.h"
#include "../../common.h"
#include <thread>
#include <mutex>


OBJparser::OBJparser()
{
}


OBJparser::~OBJparser()
{
}

void OBJparser::read(GXE_Flags flags)
{
	if (flags & GXE_OBJ_DATA || flags & GXE_BIN_DATA_PARSE)
	{
		if (common::fileCheck("DATA/Models/" + path + ".bin"))
		{
			std::cout << "[Parser] DATA/Models/" + path + ".bin" << " exists, using it instead!" << std::endl;
			loadFromBin(path);
			return;
		}
		std::cout << "[Parser] DATA/Models/" + path + ".bin" << " does not exists, creating one!" << std::endl;
		FILE* f = fopen(("DATA/Objects/" + path + ".obj").c_str(), "r");
		if (f == NULL)
		{
			throw std::runtime_error("[Parser] File can't be accessed at: DATA/Objects/" + path + ".obj" + " (wavefront)");
			return;
		}

		//Read all the file data
		char buffer[256];
		printf("[OBJparser] Reading file...\n");
		while (fgets(buffer, 256, f) != nullptr)
		{
			data.push_back(str::string(buffer));
		}

		//Temporary data
		std::vector<glm::vec2> tuvs;
		std::vector<glm::vec3> tnrm;
		std::vector<unsigned int> uvs_ind;
		std::vector<unsigned int> nrm_ind;

		glm::vec2* uvi;
		glm::vec3* nmi;

		//Vertex loading
		int i = 0;
		printf("[OBJparser] Loading vertices...\n");
		while (true)
		{
			i++; //First line not important anyways
			if (data[i].startsWith("v "))
			{
				glm::vec3 posData = parseVec3(data[i]);
				vertices.push_back(posData);
				vList.push_back(LinkedVertex(vertices.size(), posData));
			}
			else if (data[i].startsWith("vt "))
				tuvs.push_back(parseVec2(data[i]));
			else if (data[i].startsWith("vn "))
				tnrm.push_back(parseVec3(data[i]));
			else if (data[i].startsWith("f "))
			{
				printf("[OBJparser] Loaded %d vertices.\n", vertices.size());
				uvi = (glm::vec2*)malloc(sizeof(glm::vec2) * vertices.size());
				nmi = (glm::vec3*)malloc(sizeof(glm::vec3) * vertices.size());
				break;
			}
			else //Skip materials, objects and comments (for now)
				continue;
		}

		printf("[OBJparser] Parsing faces...\n");
		for (int z = i; z < data.size(); z++)
		{
			if (!data[z].startsWith("f "))
				continue; //Line doesn't start with f
			std::vector<str::string> result = data[z].split(" ");
			std::vector<str::string> f1 = result[1].split("/");
			std::vector<str::string> f2 = result[2].split("/");
			std::vector<str::string> f3 = result[3].split("/");

			parseFace(f1, indices, uvi, nmi, tuvs, tnrm);
			parseFace(f2, indices, uvi, nmi, tuvs, tnrm);
			parseFace(f3, indices, uvi, nmi, tuvs, tnrm);
		}

		//Coordinate rearrange
		printf("[OBJparser] Rearanging coordinates...\n");
		std::thread w0([=](void) -> void { for (int w = 0; w < vertices.size(); w++) { uvs.push_back(uvi[w]); }});
		for (int x = 0; x < vertices.size(); x++)
		{
			normals.push_back(nmi[x]);
		}
		w0.join();

		free(uvi);
		free(nmi);
		fclose(f);

		parseToBin(path);
	}

	if (flags & 0x0EF3) //No textures
	{

	}
	else //Textures
	{

	}


	if (flags & 0x0EF4) //No objects
	{

	}
	else //Objects
	{

	}


	if (flags & 0x0EF5) //No materials
	{

	}
	else //Materials
	{

	}
}

std::vector<glm::vec3> OBJparser::loadVRT()
{
	return vertices;
}

std::vector<glm::vec2> OBJparser::loadUVS()
{
	return uvs;
}

std::vector<glm::vec3> OBJparser::loadNRM()
{
	return normals;
}

std::vector<unsigned int> OBJparser::loadIND()
{
	return indices;
}
