#include "collisiontree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <gl/glew.h>

void CollisionTree::createTree(GLuint buffer)
{
	//try with or without sizeof
	GLsizei size;
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	size /= sizeof(glm::vec3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glm::vec3* buff = (glm::vec3*)glMapNamedBuffer(buffer, GL_READ_ONLY);
	std::vector<glm::vec3> vertices(buff, buff + size);
	glUnmapNamedBuffer(buffer);
	std::vector<float> vX, vY, vZ;
	int x = 0;
	int c = 0;
	for (auto v : vertices)
	{
		vX.push_back(v.x);
		vY.push_back(v.y);
		vZ.push_back(v.z);
	}
	/*FILE* f = fopen("cnt.log", "w");
	for (int i = 0; i < size; i++)
	{
		std::string s("Count: " + std::to_string(i) + " | Value: (" + std::to_string(vertices[i].x) + "; " + std::to_string(vertices[i].y) + "; " + std::to_string(vertices[i].z) + ")\n");
		const char* buffer = s.c_str();
		fwrite(buffer, strlen(buffer)+1, 1, f);
	}
	fclose(f);*/

	auto itX = std::minmax_element(vX.begin(), vX.end());
	auto itY = std::minmax_element(vY.begin(), vY.end());
	auto itZ = std::minmax_element(vZ.begin(), vZ.end());
	typedef std::tuple<std::pair<std::vector<float>::iterator, std::vector<float>::iterator>,
		std::pair<std::vector<float>::iterator, std::vector<float>::iterator>,
		std::pair<std::vector<float>::iterator, std::vector<float>::iterator>> TPL;

	TPL data = std::make_tuple(itX, itY, itZ);

	std::cout << "minX - " << *itX.first << std::endl;
	std::cout << "maxX - " << *itX.second << std::endl;

	std::cout << "minY - " << *itY.first << std::endl;
	std::cout << "maxY - " << *itY.second << std::endl;

	std::cout << "minZ - " << *itZ.first << std::endl;
	std::cout << "maxZ - " << *itZ.second << std::endl;


	boundingVertices = {
		glm::vec3(*itX.first, *itY.second, *itZ.second),     // Front-top-left
		glm::vec3(*itX.second, *itY.second, *itZ.second),      // Front-top-right
		glm::vec3(*itX.first, *itY.first, *itZ.second),    // Front-bottom-left
		glm::vec3(*itX.second, *itY.first, *itZ.second),     // Front-bottom-right
		glm::vec3(*itX.second, *itY.first, *itZ.first),    // Back-bottom-right
		glm::vec3(*itX.second, *itY.second, *itZ.second),      // Front-top-right
		glm::vec3(*itX.second, *itY.second, *itZ.first),     // Back-top-right
		glm::vec3(*itX.first, *itY.second, *itZ.second),     // Front-top-left
		glm::vec3(*itX.first, *itY.second, *itZ.first),    // Back-top-left
		glm::vec3(*itX.first, *itY.first, *itZ.second),    // Front-bottom-left
		glm::vec3(*itX.first, *itY.first, *itZ.first),   // Back-bottom-left
		glm::vec3(*itX.second, *itY.first, *itZ.first),    // Back-bottom-right
		glm::vec3(*itX.first, *itY.second, *itZ.first),    // Back-top-left
		glm::vec3(*itX.second, *itY.second, *itZ.first)      // Back-top-right
	};

	drawOrder = 
	{
		0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1,
	};

	first = new CollisionNode(0, NULL);

	for (int i = 0; i < 8; i++)
	{
		first->childs[i] = new CollisionNode(1, first);
		for (int j = 0; j < 8; j++)
		{
			first->childs[i]->childs[j] = new CollisionNode(2, first->childs[i]);
			for (int k = 0; k < 8; k++)
			{
				first->childs[i]->childs[j]->childs[k] = new CollisionNode(3, first->childs[i]->childs[j]);
				for (int l = 0; l < 8; l++)
				{
					first->childs[i]->childs[j]->childs[k]->childs[l] = new CollisionNode(4, first->childs[i]->childs[j]->childs[k]);
				}
			}
		}
	}

	labelTree(first, vertices, boundingVertices.data());
}

std::vector<glm::vec3> CollisionTree::getBoundingVertices()
{
	return boundingVertices;
}

std::vector<unsigned int> CollisionTree::getBoundingVerticesIndices()
{
	return drawOrder;
}

void CollisionTree::labelTree(CollisionNode * first, std::vector<glm::vec3> & vertices, glm::vec3 verts[])
{
	for (int i = 0; i < 8; i++)
	{
		first->vertices[i] = verts[i];
	}
}
