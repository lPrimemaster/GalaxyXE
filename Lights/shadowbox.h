#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "../camera.h"
#include "light.h"

#define GXE_SHADOW_OFFSET 10
#define GXE_SHADOW_DISTANCE 100
#define GXE_UP()\
glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)
#define GXE_FORWARD()\
glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)

class ShadowBox
{
public:
	ShadowBox(Camera* cam, Light* light);
	~ShadowBox();

	void update();

	const float getWidth() const;
	const float getHeight() const;
	const float getLenght() const;
	const glm::vec3 getCenter() const;

private:
	void calculateHWValues();
	std::vector<glm::vec4> calculateFVertices(glm::mat4& rotation, glm::vec3 forwardVec, glm::vec3 centerNear, glm::vec3 centerFar);
	glm::vec4 calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction, float width);

	float minX, maxX;
	float minY, maxY;
	float minZ, maxZ;
	float farHeight, farWidth;
	float nearHeight, nearWidth;

	glm::mat4 lightViewMatrix;

	Light* light;
	Camera* cam;
};

