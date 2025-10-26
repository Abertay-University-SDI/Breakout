#include "math.h"

float Math::lerp(const float a, const float b, const float alpha)
{
	return a * (1 - alpha) + b * alpha;
}

float Math::normalizeRange(const float min, const float max, const float value)
{
	return (value - min) / (max - min);
}
