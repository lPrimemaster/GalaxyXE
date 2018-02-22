#pragma once
#include "light.h"
#include <map>

#define BINDING_INDEX 1


struct Shader_Application_IO
{
	Shader_Application_IO(const Light& light)
	{
		this->isEnabled = light.isOn();
		this->lightType = light.getLightType();
		this->position = light.getPosition();
		this->direction = light.getDirection();
		this->color = light.getColor();
		this->ambient = light.getAmbientColor();
		this->coneDirection = light.getConeDirection();
		this->spotCosCutoff = light.getSpotCosCutoff();
		this->spotExponent = light.getSpotExponent();
		this->constAtt = light.getConstAtt();
		this->linearAtt = light.getLinearAtt();
		this->quadAtt = light.getQuadAtt();
	}

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;
	glm::vec3 ambient;

	glm::vec3 coneDirection;

	bool isEnabled;
	unsigned int lightType;
	
	float spotCosCutoff;
	float spotExponent;

	float constAtt;
	float linearAtt;
	float quadAtt;

	std::map<std::string, int> a;
};

size_t TypeSize(GLenum type);

const bool sendLightProperties(GLuint programID, const Light& light, std::string uniformBlockName, unsigned int index);