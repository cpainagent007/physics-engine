#include "gravitationEffector.h"

#include <iostream>

void GravitationEffector::Apply(std::vector<Body>& inBodies)
{
	std::vector<Body*> outBodies;
	CollectBodiesInside(inBodies, outBodies);

	for (int i = 0; i < outBodies.size(); ++i)
	{
		for (int j = i + 1; j < outBodies.size(); ++j)
		{
			Body* bodyA = outBodies[i];
			Body* bodyB = outBodies[j];

			Vector2 direction = bodyA->position - bodyB->position;
			float distance = Vector2Length(direction);

			distance = fmaxf(distance, 1.0f);

			float forceMagnitude = strength * ((bodyA->mass * bodyB->mass) / (distance * distance));

			Vector2 forceDirection = Vector2Normalize(direction) * forceMagnitude;

			bodyA->AddForce(forceDirection * -1);
			bodyB->AddForce(forceDirection);
		}
	}
}

void GravitationEffector::Draw()
{
	Effector::Draw();
	DrawCircleV(position, size, Fade(YELLOW, 0.2f));
}