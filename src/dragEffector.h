#pragma once

#include "effector.h"

class DragEffector : public Effector
{
public:
	DragEffector(Vector2 position, float size, float drag) :
		Effector{ position, size }, drag{ drag }
	{}

	void Apply(std::vector<Body>& inBodies) override;
	void Draw() override;

private:
	float drag;
};