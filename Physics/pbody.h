#pragma once
#include <glm\glm.hpp>
#include "collisiontree.h"
#include "../Entities/entity.h"

#define GXE_POSITION 0x77
#define GXE_VELOCITY 0x78
#define GXE_ACCELERATION 0x80
#define GXE_ROTATION 0x81
#define GXE_ANGULAR_VELOCITY 0x82
#define GXE_ANGULAR_ACCELERATION 0x83
#define GXE_LINEAR_MOMENTUM 0x84
#define GXE_ANGULAR_MOMENTUM 0x85

class PBody
{
public:
	friend class PEngine;
	typedef int GXE_Flags;
	PBody(Entity* ent);
	~PBody();

	inline glm::vec3 getPosition()
	{
		return position;
	}
	inline glm::vec3 getRotation()
	{
		return rotation;
	}
	inline CollisionTree getColisionTree()
	{
		return tree;
	}

	bool recieveParam(GXE_Flags paramType, glm::vec3 param);

private:
	//3 Dimensional Space Properties -- Also some phase space
	glm::vec3 position;
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);

	glm::vec3 linearMomentum;
	glm::vec3 angularMomentum;

	glm::vec3 rotation;
	glm::vec3 angularVelocity = glm::vec3(0.0f);
	glm::vec3 angularAcceleration = glm::vec3(0.0f);

	double mass;
	double inverse_mass;

	glm::mat3 inertiaTensor;

	Entity* ent;

	CollisionTree tree;

};

