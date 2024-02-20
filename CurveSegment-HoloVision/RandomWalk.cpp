#include "RandomWalk.h"

RandomWalk::RandomWalk(int height, int width)
	:
	height(height),
	width(width),
	rng(std::random_device()()),
	heightDistribution(0, height - 1),
	widthDistribution(0, width - 1)
{
}

std::vector<Vec2<int>> RandomWalk::generateCurveSegment(int length)
{
	//Start at a random position in the image
	std::vector<Vec2<int>> curveSegment;
	Vec2<int> currentPosition{heightDistribution(rng), widthDistribution(rng)};
	curveSegment.emplace_back(currentPosition);

	for (int i = 1; i < length; ++i)
	{
		//Take a step in a random direction.
		auto walkDirection = RandomWalk::Direction(directionDistribution(rng));
		switch (walkDirection)
		{
		case RandomWalk::Direction::UP:
			currentPosition = {currentPosition.x, std::max(0,currentPosition.y - 1)};
			break;
		case RandomWalk::Direction::RIGHT:
			currentPosition = { std::min( width - 1, currentPosition.x + 1), currentPosition.y };
			break;
		case RandomWalk::Direction::BOTTOM:
			currentPosition = { currentPosition.x, std::min(height - 1,currentPosition.y + 1) };
			break;
		case RandomWalk::Direction::LEFT:
			currentPosition = { std::max(0, currentPosition.x - 1), currentPosition.y };
			break;
		default:
			break;
		}
		curveSegment.emplace_back(currentPosition);
	}

	return curveSegment;
}
