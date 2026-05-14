#include "dragEffector.h"

void AreaEffector::Apply(std::vector<Body>& inBodies)
{
	force = Vector2Negate(body.velocity) * drag;
	body.AddForce(force);
}

void AreaEffector::Draw()
{
	Effector::Draw();
	DrawCircleV(position, size, Fade(PURPLE, 0.2f));
}
