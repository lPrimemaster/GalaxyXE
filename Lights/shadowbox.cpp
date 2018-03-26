#include "shadowbox.h"



ShadowBox::ShadowBox(Camera* cam, Light* light)
{
	this->cam = cam;
	this->light = light;
	calculateHWValues();
}


ShadowBox::~ShadowBox()
{
}

void ShadowBox::update()
{
	glm::mat4 rot = glm::mat4();
	glm::rotate(rot, glm::radians(-cam->getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::rotate(rot, glm::radians(-cam->getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));

	glm::vec4 forward = rot * GXE_FORWARD();
	glm::vec3 toFar = glm::vec3(forward);
	toFar = toFar * float(GXE_SHADOW_DISTANCE);

	glm::vec3 toNear = glm::vec3(forward);
	toNear = toNear * 0.1f;

	glm::vec3 centerNear = toNear + cam->getEye();

	glm::vec3 centerFar = toFar + cam->getEye();

	std::vector<glm::vec4> points = calculateFVertices(rot, forward, centerNear, centerFar);

	bool first = true;
	for (auto point : points)
	{
		if (first)
		{
			minX = point.x;
			maxX = point.x;
			minY = point.y;
			maxY = point.y;
			minZ = point.z;
			maxZ = point.z;
			first = false;
			continue;
		}
		if (point.x > maxX)
			maxX = point.x;
		else if (point.x < minX)
		{
			minX = point.x;
		}
		if (point.y > maxY)
			maxY = point.y;
		else if (point.y < minY)
		{
			minY = point.y;
		}
		if (point.z > maxZ)
			maxZ = point.z;
		else if (point.z < minZ)
		{
			minZ = point.z;
		}
	}
	maxZ += GXE_SHADOW_OFFSET;

}

const float ShadowBox::getWidth() const
{
	return maxX - minX;
}

const float ShadowBox::getHeight() const
{
	return maxY - minY;
}

const float ShadowBox::getLenght() const
{
	return maxZ - minZ;
}

const glm::vec3 ShadowBox::getCenter() const
{
	float x = minX + maxX;
	float y = minY + maxY;
	float z = minZ + maxZ;

	x /= 2.0f;
	y /= 2.0f;
	z /= 2.0f;

	glm::vec4 center = glm::vec4(x, y, z, 1.0f);

	return glm::vec3(glm::inverse(cam->getViewMatrix()) * center);
}

void ShadowBox::calculateHWValues()
{
	farWidth = GXE_SHADOW_DISTANCE * glm::tan(glm::radians(cam->getFOV()));
	nearWidth = 0.1f * glm::tan(glm::radians(cam->getFOV()));

	farHeight /= cam->getAspectRatio();
	nearWidth /= cam->getAspectRatio();
}

std::vector<glm::vec4> ShadowBox::calculateFVertices(glm::mat4 & rotation, glm::vec3 forwardVec, glm::vec3 centerNear, glm::vec3 centerFar)
{
	glm::vec3 upVec      = rotation * GXE_UP();
	glm::vec3 rightVec   = glm::cross(forwardVec, upVec);
	glm::vec3 downVec    = -upVec;
	glm::vec3 leftVec    = -rightVec;

	glm::vec3 farTop     = centerFar + upVec * farHeight;
	glm::vec3 farBottom  = centerFar + downVec * farHeight;
	glm::vec3 nearTop    = centerNear + upVec * nearHeight;
	glm::vec3 nearBottom = centerNear + downVec * nearHeight;

	std::vector<glm::vec4> points;
	points.reserve(8);
	points.push_back(calculateLightSpaceFrustumCorner(farTop, rightVec, farWidth));
	points.push_back(calculateLightSpaceFrustumCorner(farTop, leftVec, farWidth));

	points.push_back(calculateLightSpaceFrustumCorner(farBottom, rightVec, farWidth));
	points.push_back(calculateLightSpaceFrustumCorner(farBottom, leftVec, farWidth));

	points.push_back(calculateLightSpaceFrustumCorner(nearTop, rightVec, nearWidth));
	points.push_back(calculateLightSpaceFrustumCorner(nearTop, leftVec, nearWidth));

	points.push_back(calculateLightSpaceFrustumCorner(nearBottom, rightVec, nearWidth));
	points.push_back(calculateLightSpaceFrustumCorner(nearBottom, leftVec, nearWidth));

	return points;
}

glm::vec4 ShadowBox::calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction, float width)
{
	glm::vec3 point = startPoint + direction * width;
	glm::vec4 point4 = glm::vec4(point, 1.0f);

	return cam->getViewMatrix() * point4;
}
