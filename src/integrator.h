#pragma once
#include "body.h"

class Integrator
{
public:
	static inline void ExplicitEuler(Body& body, float dt)
	{
		body.position += body.velocity * dt;
		body.velocity += body.acceleration * dt;
		body.velocity *= (1.0f / (1.0f + body.damping * dt));
	}

	static inline void SemiImplicitEuler(Body& body, float dt)
	{
		body.velocity += body.acceleration * dt;
		body.velocity *= (1.0f / (1.0f + body.damping * dt));
		body.position += body.velocity * dt;
	}
};