#include "light.h"

void Light::setAttenuationFunc(float constAttenuation, float linearAttenuation, float quadAttenuation)
{
	this->constAtt = constAttenuation;
	this->linearAtt = linearAttenuation;
	this->quadAtt = quadAttenuation;
}

void Light::setPosition(glm::vec3 newPos)
{
	this->position = newPos;
}

void Light::setDirection(glm::vec3 newDir)
{
	this->direction = newDir;
}

const glm::vec3 Light::getPosition() const
{
	return position;
}

const glm::vec3 Light::getColor() const
{
	return color;
}

const glm::vec3 Light::getAmbientColor() const
{
	return ambientColor;
}

const float Light::getShininess() const
{
	return shininess;
}

const float Light::getStrength() const
{
	return stregth;
}

const float Light::getConstAtt() const
{
	return constAtt;
}

const float Light::getLinearAtt() const
{
	return linearAtt;
}

const float Light::getQuadAtt() const
{
	return quadAtt;
}

const unsigned int Light::getLightType() const
{
	return lightType;
}

const bool Light::isOn() const
{
	return state;
}

glm::mat4 & Light::getDepthBiasMatrix()
{
	return depthBias;
}

Light::Light()
{
}
