#include "GlobFunc.h"

int GlobFunc::Clamp(int value, const int min, const int max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

float GlobFunc::Clamp(float value, const float min, const float max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

glm::vec3 GlobFunc::Clamp(glm::vec3 value, const float min, const float max)
{
	value.x = GlobFunc::Clamp(value.x, min, max);
	value.y = GlobFunc::Clamp(value.y, min, max);
	value.z = GlobFunc::Clamp(value.z, min, max);
	return value;
}

glm::vec2 GlobFunc::Clamp(glm::vec2 value, const float min, const float max)
{
	value.x = GlobFunc::Clamp(value.x, min, max);
	value.y = GlobFunc::Clamp(value.y, min, max);
	return value;
}

int GlobFunc::Modulo(int value, const int min, const int max)
{
	while (value < min) value += (max - min);
	while (value >= max) value -= (max - min);
	return value;
}

float GlobFunc::Modulo(float value, const float min, const float max)
{
	while (value < min) value += (max - min);
	while (value >= max) value -= (max - min);
	return value;
}

glm::vec3 GlobFunc::Modulo(glm::vec3 value, const float min, const float max)
{
	value.x = GlobFunc::Modulo(value.x, min, max);
	value.y = GlobFunc::Modulo(value.y, min, max);
	value.z = GlobFunc::Modulo(value.z, min, max);
	return value;
}

glm::vec2 GlobFunc::Modulo(glm::vec2 value, const float min, const float max)
{
	value.x = GlobFunc::Modulo(value.x, min, max);
	value.y = GlobFunc::Modulo(value.y, min, max);
	return value;
}