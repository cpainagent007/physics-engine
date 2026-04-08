#pragma once
#include "body.h"
#include "raylib.h"
#include "raymath.h"
#include "random.h"
#include "integrator.h"
#include "effector.h"
#include "pointEffector.h"

#include <vector>

class World
{
public:
	World() : gravity{ 0, 9.81f }, mouseActive(false), mouseRepel(true), mousePosition{ 0, 0 }
	{
		//bodies.reserve(10000);
	}

	void Step(float dt);
	void Draw() const;
	void AddBody(Body& body);
	void AddEffector(Effector* effector);

	std::vector<Body> bodies;
	std::vector<Effector*> effectors;

	Vector2 gravity;
	bool mouseActive;
	bool mouseRepel;
	Vector2 mousePosition;
};