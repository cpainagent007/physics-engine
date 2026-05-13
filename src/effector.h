#pragma once

#include "body.h"

#include <vector>

class Effector
{
public:
	Effector(Vector2 position, float size) : 
		position{ position }, size{ size }
	{}

	virtual void Apply(std::vector<Body>& bodies) = 0;
	virtual void Draw();

protected:
	Vector2 position;
	float size;
};