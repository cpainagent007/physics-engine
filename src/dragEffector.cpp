#include "dragEffector.h"

void DragEffector::Apply(std::vector<Body>& inBodies)
{
	std::vector<Body*> outBodies;
	CollectBodiesInside(inBodies, outBodies);

	for (auto& body : outBodies)
	{
		Vector2 force = Vector2Negate(body->velocity) * drag;
		body->AddForce(force);
	}
}

void DragEffector::Draw()
{
	Effector::Draw();
	DrawCircleV(position, size, Fade(PURPLE, 0.2f));
}
