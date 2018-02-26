#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "../common.h"
#include "../Utils/math.h"
#include "../camera.h"

#define GXE_DIRECTIONAL_LIGHT    0x0F0
#define GXE_SPOT_LIGHT           0x0F1
#define GXE_POINT_LIGHT          0x0F2
#define GXE_MAX_LIGHT_PROPERTIES 0x0C
#define GXE_MAX_LIGHTS           0x02

class Light
{
public:

	void setAttenuationFunc(float constAttenuation, float linearAttenuation, float quadAttenuation);
	void setPosition(glm::vec3 newPos);
	void setDirection(glm::vec3 newDir);


	//Getters
	const glm::vec3 getPosition() const;
	const glm::vec3 getColor() const;
	const glm::vec3 getAmbientColor() const;
	virtual const glm::vec3 getDirection() const = 0;
	virtual const glm::vec3 getConeDirection() const = 0;

	virtual const float getSpotCosCutoff() const = 0;
	virtual const float getSpotExponent() const = 0;

	const float getShininess() const;
	const float getStrength() const;

	const float getConstAtt() const;
	const float getLinearAtt() const;
	const float getQuadAtt() const;

	const unsigned int getLightType() const;

	const bool isOn() const;

	glm::mat4& getDepthBiasMatrix();

	//OpenGL interface

protected:
	Light();
	//Main attributes
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 ambientColor = color;

	glm::vec3 coneDirection = glm::vec3(0.0f, -1.0f, 0.0f);
	float spotCosCutoff = 0.5f;
	float spotExponent = 2.0f;

	//Reflection properties
	float shininess = 2;
	float stregth = 5;

	//Attenuation values for light distance / ambient reflection
	float ambientAttenuation = 0.1f;
	float constAtt = 1.0f;
	float linearAtt = 1.0f;
	float quadAtt = 1.0f;

	unsigned int lightType = 0x0;
	bool state = true;

private:
	glm::mat4 depthBias;
};
