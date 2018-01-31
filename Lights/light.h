#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "../common.h"
#include "../Utils/math.h"
#include "../camera.h"

class Light
{
public:
	void enable()
	{
		properties.isEnabled = true;
	}

	void disable()
	{
		properties.isEnabled = false;
	}

	void setProperties(LightProperties lp)
	{
		properties = lp;
		changed = true;
	}

	void computeHalfVector(Camera cam)
	{
		properties.halfVector = math::normalize(cam.getEye() + properties.position);
		changed = true;
	}

	const int getType() const
	{
		return properties.type;
	}

	const glm::vec3 getColor() const
	{
		return properties.color;
	}

	const glm::vec3 getAmbient() const
	{
		return properties.ambient;
	}

	const glm::vec3 getPosition() const
	{
		return properties.position;
	}

	const glm::vec3 getConeDirection() const
	{
		return properties.coneDirection;
	}

	const glm::vec3 getHalfVector() const
	{
		return properties.halfVector;
	}

	const float getSpotCosCutoff() const
	{
		return properties.spotCosCutoff;
	}

	const float getSpotExponent() const
	{
		return properties.spotExponent;
	}

	const float getConstantAttenuation() const
	{
		return properties.constantAttenuation;
	}

	const float getLinearAttenuation() const
	{
		return properties.linearAttenuation;
	}

	const float getQuadraticAttenuation() const
	{
		return properties.quadraticAttenuation;
	}

	const bool isEnabled() const 
	{
		return properties.isEnabled;
	}

	const bool isChanged() const
	{
		return changed;
	}

	int& ID()
	{
		return lID;
	}

	void mark()
	{
		changed = false;
	}

private:
	LightProperties properties;
	int lID = -1;
	bool changed = false;
};
