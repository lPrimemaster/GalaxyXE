#include "lvertex.h"

LinkedVertex::LinkedVertex(unsigned int vPointer, glm::vec3 position)
{
	this->vPointer = vPointer;
	this->position = position;
}


LinkedVertex::~LinkedVertex()
{
	delete next;
}
