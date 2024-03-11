#include "GameObjectInstance.h"

GameObjectInstance::GameObjectInstance(unsigned int frameSpeed)
{
	Position = glm::vec3(0.0f);
	Rotation = glm::vec3(0.0f);
	Scale = glm::vec3(1.0f);

	ModelMatrix = glm::mat4(1.0f);

	BaseColor = glm::vec4(1.0f);
	OwnColor = false;

	CurrFrame = 0;
	CurrImage = 0;
	Shift = glm::vec2(0.0f);
	ShiftSpeed = glm::vec2(0.0f);
	FrameSpeed = frameSpeed;

	StencilId = 0;

	Ui = false;
	Draw = true;
}

void GameObjectInstance::Transform(const glm::vec3 translate, const glm::vec3 rotate, const glm::vec3 scale, const bool newTransform)
{
	glm::mat4 newMatrix = glm::mat4(1.0f);
	if (newTransform)
	{
		Position = translate;
		Rotation = GlobFunc::Modulo(rotate, 0.0f, 360.0f);
		Scale = scale;
	}
	else
	{
		Position = Position + translate;
		Rotation = GlobFunc::Modulo(Rotation + rotate, 0.0f, 360.0f);
		Scale = Scale * scale;
	}
	ModelMatrix = glm::translate(newMatrix, Position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, Scale);
}

void GameObjectInstance::Move(float amount, float deltaTime, float up)
{
	glm::vec3 direction;
	direction.x = sin(glm::radians(Rotation.y));
	direction.y = up;
	direction.z = cos(glm::radians(Rotation.y));
	GameObjectInstance::Transform(direction * amount * deltaTime * (-1.0f), glm::vec3(0.0f), glm::vec3(1.0f), false);
}

void GameObjectInstance::Rotate(float amount, float deltaTime)
{
	GameObjectInstance::Transform(glm::vec3(0.0f), glm::vec3(0.0f, amount + deltaTime, 0.0f), glm::vec3(1.0f), false);
}

void GameObjectInstance::ChangeColor(glm::vec4 baseColor)
{
	OwnColor = true;
	BaseColor = baseColor;
}