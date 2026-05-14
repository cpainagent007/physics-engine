#include "areaEffector.h"

void AreaEffector::Apply(std::vector<Body>& inBodies)
{
	std::vector<Body*> outBodies;
	CollectBodiesInside(inBodies, outBodies);

	for (auto& body : outBodies)
	{
		Vector2 direction = Vector2{ cosf(angle * DEG2RAD), sinf(angle * DEG2RAD) };

		Vector2 force = direction * forceMagnitude;
		body->AddForce(force);
	}
}

void AreaEffector::Draw()
{
	Effector::Draw();
	DrawCircleV(position, size, Fade(BLUE, 0.2f));
}
