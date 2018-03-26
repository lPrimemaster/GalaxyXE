#include "collisionnode.h"


CollisionNode::CollisionNode(unsigned int lvl, CollisionNode* parent)
{
	level = lvl;
	this->parent = parent;
}

CollisionNode::~CollisionNode()
{
}

void CollisionNode::calculateSubdivide(CollisionNode * node)
{
	if (node == NULL)
	{
		//Then we are calculating a level zero subdivider
	}
	else
	{

	}
}

void CollisionNode::setMinMaxValues(float mX, float MX, float mY, float MY, float mZ, float MZ)
{
	minX = mX;
	maxX = MX;
	minY = mY;
	maxY = MY;
	minZ = mZ;
	maxZ = MZ;
}
