#pragma once
#include "raylib.h"

class Random
{
public:
	inline static float GetRandomFloat()
	{
		return GetRandomValue(0, 10000) / (float)10000;
	}

	inline static float GetRandomFloat(float max)
	{
		return GetRandomValue(0, (float)max) / max;
	}

	inline static float GetRandomFloat(float min, float max)
	{
		return GetRandomValue((float)min, (float)max) / max;
	}

	inline static Color GetRandomColor()
	{
		Color colors[] = { MAROON, RED, PINK, ORANGE, GOLD, YELLOW, DARKGREEN, LIME, GREEN, DARKBLUE, BLUE, SKYBLUE, DARKPURPLE, VIOLET, PURPLE };
		int colorsAmount = sizeof(colors) / sizeof(colors[0]);
		return colors[GetRandomValue(0, (colorsAmount - 1))];
	}
};