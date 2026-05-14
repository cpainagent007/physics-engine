#pragma once

#include "effector.h"

class AreaEffector : public Effector
{
public:
	AreaEffector(Vector2 position, float size, float angle, float forceMagnitude) :
		Effector{ position, size }, angle{ angle }, forceMagnitude{ forceMagnitude }
	{}

	void Apply(std::vector<Body>& inBodies) override;
	void Draw() override;

private:
	float angle;
	float forceMagnitude;
};