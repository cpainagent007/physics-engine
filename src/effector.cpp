#include "effector.h"

void Effector::Draw()
{
	DrawCircleLinesV(position, size, WHITE);
}

void Effector::CollectBodiesInside(std::vector<Body>& inBodies, std::vector<Body*>& outBodies)
{
	for (auto& body : inBodies)
	{
		if (Vector2DistanceSqr(body.position, position) < (size * size))
		{
			outBodies.push_back(&body);
		}
	}
}