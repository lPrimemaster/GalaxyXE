#include "pbody.h"
#include "../Models/model.h"


PBody::PBody(Entity* ent) : ent(ent)
{
	ent->operator()(this);
	tree.createTree(ent->getModel().getBuffers()["VRT"]);
}


PBody::~PBody()
{
}

bool PBody::recieveParam(GXE_Flags paramType, glm::vec3 param)
{
	switch (paramType)
	{
	case GXE_POSITION:
		position = param;
		break;
	case GXE_VELOCITY:
		velocity = param;
		break;
	case GXE_ACCELERATION:
		acceleration = param;
		break;
	case GXE_ROTATION:
		rotation = param;
		break;
	case GXE_ANGULAR_VELOCITY:
		angularVelocity = param;
		break;
	case GXE_ANGULAR_ACCELERATION:
		angularAcceleration = param;
		break;
	case GXE_LINEAR_MOMENTUM:
		linearMomentum = param;
		break;
	case GXE_ANGULAR_MOMENTUM:
		angularMomentum = param;
		break;
	default:
		break;
	}
	return true;
}
