#pragma once
#include <iostream>

struct CollisionBox
{
	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	bool checkInside(CollisionBox b)
	{
		using namespace phys;
	}
};

namespace phys
{
	bool checkBoundaries(CollisionBox a, CollisionBox b)
	{

	}

	//test
	constexpr long double operator"" d(long double degrees)
	{
		return degrees * 3.141592654 / 180;
	}
}
