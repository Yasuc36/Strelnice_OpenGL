#pragma once

#include "pgr.h"
#include "GlobFunc.h"

/**
 * \brief Instance of GameObject. Contains all info neede for each instance
 */
class GameObjectInstance
{
public:
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	glm::mat4 ModelMatrix;  ///< Used for transformation

	glm::vec4 BaseColor;   ///< Instance color replaces GO color, if wanted
	bool OwnColor;  ///< Does it have own color specified for this instace?

	unsigned int CurrFrame;  ///< Current vertex frame
	unsigned int CurrImage;  ///< Current texture image (individual image of complete texture)
	glm::vec2 Shift;  ///< Specify direction of shift of the texture in X,Y axis
	glm::vec2 ShiftSpeed;  ///< Specify amount of shift of the texture in X,Y axis
	unsigned int FrameSpeed;  ///< Speed of vertex change

	unsigned char StencilId;  ///< ID used in stencil buffer to identify objects, that are clicked on

	bool Ui;
	bool Draw;  ///< Should this object be drawn?



	/**
	 * \brief Constructor
	 * 
	 * \param frameSpeed Speed of vertex change
	 */
	GameObjectInstance(unsigned int frameSpeed = 1);



	/**
	 * \brief Method to change position, rotation and scale
	 * 
	 * \param translate change of position
	 * \param rotate change of rotation
	 * \param scale change of scale
	 * \param newTransform specify, if transformations should be added to existing values, or if it should specify with nulled values
	 */
	void Transform(const glm::vec3 translate, const glm::vec3 rotate, const glm::vec3 scale, const bool newTransform = true);

	/**
	 * \brief Helper method to simplify process of transforming existing position
	 * 
	 * \param amount how much to move
	 * \param deltaTime time from last frame, to make smooth movement
	 * \param up how much to move upwards/downards
	 */
	void Move(float amount, float deltaTime = 1.0f, float up = 0.0f);

	/**
	 * \brief Helper method to simplify process of transforming existing rotation
	 * 
	 * \param amount angle of rotation
	 * \param deltaTime time from last frame, to make smooth rotation
	 */
	void Rotate(float amount, float deltaTime = 1.0f);

	/**
	 * \brief method to change and activate instance color
	 * 
	 * \param baseColor color
	 */
	void ChangeColor(glm::vec4 baseColor);
};
