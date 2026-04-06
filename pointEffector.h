#pragma once

#include "effector.h"

class PointEffector : public Effector
{
public:
	PointEffector(Vector2 position, float size, float forceMagnitude, bool repel) :
		position{ position }, size{ size }, forceMagnitude{ forceMagnitude }, repel{ repel }
	{}
	void Apply(std::vector<Body>& bodies) override;
	void Draw();

private:
	Vector2 position;
	float size;
	float forceMagnitude;
	bool repel;
};