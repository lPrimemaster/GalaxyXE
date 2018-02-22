#pragma once
#include "light.h"
class SLight : public Light
{
public:
	SLight(glm::vec3 position, glm::vec3 color, glm::vec3 coneDirection);

	const glm::vec3 getDirection() const override;
	const float getSpotCosCutoff() const override;
	const float getSpotExponent() const override;
	const glm::vec3 getConeDirection() const override;
};

