#pragma once

#include "pgr.h"

/**
 * \brief Camera class. Contains all variables used to setup and control Camera.
 */
class Camera
{
public:
	glm::vec3 Position;  ///< World position
	glm::vec3 Front;  ///< Direction of view
	glm::vec3 Up;  ///< Up fector of view 
	float Speed;  ///< Basic speed of the movement, if the camera position is controled.
	float SpeedSprint;  ///< Faster speed of the movement, if the camera position is controled.
	float Sensitivity;  ///< Sensitivity factor
	float SensitivityX;  ///< Sensitivity for x axis
	float SensitivityY;  ///< Sensitivity for y axis
	float Yaw;  ///< Yaw angle
	float Pitch;  ///< Pitch angle



	//! Constructor
	Camera();
};

