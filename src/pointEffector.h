#pragma once

#include "effector.h"

class PointEffector : public Effector
{
public:
	PointEffector(Vector2 position, float size, float forceMagnitude, bool repel) :
		Effector{ position, size }, forceMagnitude{ forceMagnitude }, repel{ repel }
	{}

	void Apply(std::vector<Body>& inBodies) override;
	void Draw() override;

private:
	float forceMagnitude;
	bool repel;
};