#pragma once
#include <glm/glm.hpp>
#define GXE_NO_INDEX -1

class LinkedVertex
{
public:
	LinkedVertex(unsigned int vPointer, glm::vec3 position);
	~LinkedVertex();

	inline void setTextureIndex(unsigned int uvPointer)
	{
		this->uvPointer = uvPointer;
	}

	inline void setNormalIndex(unsigned int nPointer)
	{
		this->nPointer = nPointer;
	}

	inline void setDuplicate(LinkedVertex* duplicate)
	{
		next = duplicate;
	}

	inline bool isSet()
	{
		if (uvPointer == GXE_NO_INDEX && nPointer == GXE_NO_INDEX)
			return false;
		return true;
	}

	inline bool checkPointers(unsigned int uvPointer, unsigned int nPointer)
	{
		return (uvPointer == this->uvPointer && nPointer == this->nPointer);
	}

	inline LinkedVertex* getDuplicate()
	{
		return next;
	}

	inline unsigned int getvPointer()
	{
		return vPointer;
	}

	inline glm::vec3 getPosition()
	{
		return position;
	}

private:
	unsigned int vPointer = GXE_NO_INDEX;
	unsigned int uvPointer = GXE_NO_INDEX;
	unsigned int nPointer = GXE_NO_INDEX;
	glm::vec3 position;

	LinkedVertex* next = NULL;
};

