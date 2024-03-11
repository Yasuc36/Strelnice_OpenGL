#include "Camera.h"

Camera::Camera()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	Speed = 0.005f;
	SpeedSprint = Speed * 2.0f;
	Sensitivity = 0.1f;
	SensitivityX = Sensitivity * 0.8f;
	SensitivityY = Sensitivity / 4.0f;
	SensitivityY;
	Yaw = -90.0f;
	Pitch = 0.0f;
}