#pragma once
#include <map>
#include <vector>
#include "collisionnode.h"
#include <glm/glm.hpp>
#include <gl/glew.h>

#define GXE_COLLISION_MAX_SUBDIVIDE 5

class CollisionTree
{
public:
	CollisionTree() = default;
	~CollisionTree() = default;
	void createTree(GLuint buffer);
	std::vector<glm::vec3> getBoundingVertices();
	std::vector<unsigned int> getBoundingVerticesIndices();

private:
	void labelTree(CollisionNode* first, std::vector<glm::vec3> & vertices, glm::vec3 verts[]);
	CollisionNode* first;
	std::map<int, std::vector<CollisionNode*>> nodes;

	//Draw helper
	std::vector<glm::vec3> boundingVertices;
	std::vector<unsigned int> drawOrder;
};

