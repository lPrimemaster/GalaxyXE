#include "OBJparser.h"



OBJparser::OBJparser()
{
}


OBJparser::~OBJparser()
{
}

void OBJparser::read(GXE_Flags flags)
{
	f = fopen(path.c_str(), "r");
	if (f == NULL)
	{
		throw std::runtime_error("[Parser] File can't be accessed at: " + path + " (wavefront)");
		return;
	}
	
	//Read all the file data
	char buffer[256];
	while (fgets(buffer, 256, f) != nullptr)
	{
		data.push_back(str::string(buffer));
	}

	//Temporary data
	std::vector<glm::vec2> tuvs;
	std::vector<glm::vec3> tnrm;
	std::vector<unsigned int> uvs_ind;
	std::vector<unsigned int> nrm_ind;

	//Vertex loading
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].startsWith("v "))
			vertices.push_back(parseVec3(data[i]));
		else if (data[i].startsWith("vt "))
			tuvs.push_back(parseVec2(data[i]));
		else if (data[i].startsWith("vn "))
			tnrm.push_back(parseVec3(data[i]));
		else if (data[i].startsWith("f "))
			parseFace(data[i], indices, uvs_ind, nrm_ind);
		else //Skip materials, objects and comments (for now)
			continue;		
	}

	//Coordinate rearrange
	std::cout << "UInd Size:" << uvs_ind.size() << std::endl;
	std::cout << "uvs Size:" << uvs.size() << std::endl;
	for (int i = 0; i < uvs_ind.size(); i++)
	{
		uvs.push_back(tuvs[uvs_ind[i++]]);
	}
	int j = 0;
	for (auto uv : uvs)
	{
		std::cout << uv.x << " - " << uv.y << " [" << ++j << "]" << std::endl;
	}

	j = 0;
	for (auto tuv : tuvs)
	{
		std::cout << tuv.x << " - " << tuv.y << " [" << ++j << "]" << std::endl;
	}

	j = 0;
	for (auto uvi : uvs_ind)
	{
		std::cout << uvi << " [" << ++j << "]" << std::endl;
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

	fclose(f);
}

std::vector<glm::vec3> OBJparser::loadVRT()
{
	return vertices;
}

std::vector<glm::vec2> OBJparser::loadUVS()
{
	return uvs;
}

std::vector<unsigned int> OBJparser::loadIND()
{
	return indices;
}