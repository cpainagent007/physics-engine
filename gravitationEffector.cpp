#include "gravitationEffector.h"

#include <iostream>

void GravitationEffector::Apply(std::vector<Body>& bodies)
{
	for (int i = 0; i < bodies.size(); ++i)
	{
		for (int j = i + 1; j < bodies.size(); ++j)
		{
			Body& bodyA = bodies[i];
			Body& bodyB = bodies[j];

			Vector2 direction = bodyA.position - bodyB.position;
			float distance = Vector2Length(direction);

			distance = fmaxf(distance, 1.0f);

			float forceMagnitude = strength * ((bodyA.mass * bodyB.mass) / (distance * distance));

			Vector2 forceDirection = Vector2Normalize(direction) * forceMagnitude;

			bodyA.AddForce(forceDirection * -1);
			bodyB.AddForce(forceDirection);
		}
	}
}