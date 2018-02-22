#include "slight.h"



SLight::SLight(glm::vec3 position, glm::vec3 color, glm::vec3 coneDirection) : Light()
{
	//Set the light type
	lightType = GXE_SPOT_LIGHT;
	state = true;

	this->position = position;
	this->color = color;
	this->ambientColor = color;

	this->coneDirection = coneDirection;

	//Default values
	this->spotCosCutoff = 0.2f;
	this->spotExponent = 5.0f;
}

const glm::vec3 SLight::getDirection() const
{
	return glm::vec3();
}

const float SLight::getSpotCosCutoff() const
{
	return spotCosCutoff;
}

const float SLight::getSpotExponent() const
{
	return spotExponent;
}

const glm::vec3 SLight::getConeDirection() const
{
	return coneDirection;
}

