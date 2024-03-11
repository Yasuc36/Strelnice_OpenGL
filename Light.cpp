#include "Light.h"

Light::Light(glm::vec3 color)
{
	Color = color;
	Position = glm::vec3(0.0f);
	Directon = glm::vec3(0.0f, 0.0f, 1.0f);

	Constant = 1.0f;
	Linear = 0.09f;
	Quadratic = 0.032f;
	CutOff = 12.5f;

	Use = true;
}