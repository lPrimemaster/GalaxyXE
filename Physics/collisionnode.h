#pragma once
#include <iostream>
#include <glm/glm.hpp>

class CollisionNode
{
public:
	friend class CollisionTree;
	CollisionNode(unsigned int lvl, CollisionNode* parent);
	~CollisionNode();

private:
	CollisionNode* childs[8] = { NULL };
	CollisionNode* parent = NULL;
	void calculateSubdivide(CollisionNode* node);
	void setMinMaxValues(float mX, float MX, float mY, float MY, float mZ, float MZ);

	unsigned int level = 0;

private:
	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;
	glm::vec3 vertices[8] = { glm::vec3(0) };
};

