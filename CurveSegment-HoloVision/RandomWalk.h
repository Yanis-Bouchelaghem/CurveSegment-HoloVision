#pragma once
#include <vector>
#include <random>
#include "vec2.h"

class RandomWalk
{
public:
	enum class Direction
	{
		UP,
		RIGHT,
		BOTTOM,
		LEFT
	};
public:
	RandomWalk(int height, int width);
	std::vector<Vec2<int>> generateCurveSegment(int length);
private:
	const int height;
	const int width;
	std::mt19937 rng;
	std::uniform_int_distribution<int> heightDistribution;
	std::uniform_int_distribution<int> widthDistribution;
	std::uniform_int_distribution<int> directionDistribution{0,3};
};