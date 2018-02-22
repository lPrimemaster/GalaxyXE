#include "plight.h"



PLight::PLight(glm::vec3 position, glm::vec3 color) : Light()
{
	//Set the light type
	lightType = GXE_POINT_LIGHT;
	state = true;

	//Assign light properties
	this->position = position;
	this->color = color;
	this->ambientColor = color;


	//Default low attenuation
	this->constAtt = 0.1f;
	this->linearAtt = 0.1f;
	this->quadAtt = 0.1f;
}

const glm::vec3 PLight::getDirection() const
{
	return glm::vec3();
}

const float PLight::getSpotCosCutoff() const
{
	return 0.0f;
}

const float PLight::getSpotExponent() const
{
	return 0.0f;
}

const glm::vec3 PLight::getConeDirection() const
{
	return glm::vec3();
}
