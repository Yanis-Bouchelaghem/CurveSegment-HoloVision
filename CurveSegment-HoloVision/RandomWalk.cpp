#include "RandomWalk.h"

RandomWalk::RandomWalk(int height, int width)
	:
	height(height),
	width(width),
	rng(std::random_device()()),
	heightDistribution(0, height),
	widthDistribution(0, width)
{
}

std::vector<Vec2<int>> RandomWalk::generateCurveSegment(int length)
{
	std::vector<Vec2<int>> curveSegment;
	//Start at a random position in the image
	Vec2<int> currentPosition{heightDistribution(rng), widthDistribution(rng)};
	curveSegment.emplace_back(currentPosition);


	return curveSegment;
}
