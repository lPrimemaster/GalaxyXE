#include "dlight.h"



DLight::DLight(glm::vec3 direction, glm::vec3 color) : Light()
{
	//Set the light type
	lightType = GXE_DIRECTIONAL_LIGHT;
	state = true;

	//Assign light properties
	this->direction = direction;
	this->color = color;
	this->ambientColor = color;
}

const glm::vec3 DLight::getDirection() const
{
	return direction;
}

const float DLight::getSpotCosCutoff() const
{
	return spotCosCutoff;
}

const float DLight::getSpotExponent() const
{
	return spotExponent;
}

const glm::vec3 DLight::getConeDirection() const
{
	return coneDirection;
}
