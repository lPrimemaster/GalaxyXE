#pragma once
#include "light.h"

class DLight : public Light
{
public:
	DLight(glm::vec3 direction, glm::vec3 color);

	const glm::vec3 getDirection() const override;
	const float getSpotCosCutoff() const override;
	const float getSpotExponent() const override;
	const glm::vec3 getConeDirection() const override;
};

