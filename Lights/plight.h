#pragma once
#include "light.h"
class PLight : public Light
{
public:
	PLight(glm::vec3 position, glm::vec3 color);

	const glm::vec3 getDirection() const override;
	const float getSpotCosCutoff() const override;
	const float getSpotExponent() const override;
	const glm::vec3 getConeDirection() const override;
};

