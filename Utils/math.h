#pragma once
#include <glm/glm.hpp>

#define PI 3.14159265

namespace math
{
	inline double dot(glm::dvec2 a, glm::dvec2 b)
	{
		return a.x * b.x + a.y * b.y;
	}

	inline glm::vec3 cross(glm::vec3 x, glm::vec3 y)
	{
		return glm::vec3(x.y * y.z - y.y * x.z, x.z * y.x - y.z * x.x, x.x * y.y - y.x * x.y);
	}

	inline glm::dvec2 ortogonal(glm::dvec2 ref)
	{
		return glm::dvec2(-ref.y, ref.x);
	}

	inline double modulus(glm::vec3 vec)
	{
		return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}
}