#pragma once
#include "pgr.h"

/**
 * \brief Class containing all needed information for each light in the scene
 */
class Light
{
public:
	glm::vec3 Color;
	glm::vec3 Position;
	glm::vec3 Directon;

	float Constant;  ///< constant value for point light
	float Linear;  ///< linear value for point light
	float Quadratic;  ///< quadratic value for point light
	float CutOff;  ///< angle of cone for spot light

	bool Use;



	/**
	 * \brief Constructor
	 * 
	 * \param color color of emitting light
	 */
	Light(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
};