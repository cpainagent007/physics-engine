#include "pointEffector.h"

void PointEffector::Apply(std::vector<Body>& bodies)
{
	for (Body& body : bodies)
	{
		Vector2 direction;
		if (repel) direction = body.position - position;
		else direction = position - body.position;

		if (Vector2Length(direction) <= size)
		{
			Vector2 force = Vector2Normalize(direction) * forceMagnitude;
			body.AddForce(force);
		}
	}
}

void PointEffector::Draw()
{
	if (repel) DrawCircleLinesV(position, size, PINK);
	else DrawCircleLinesV(position, size, LIME);
}
