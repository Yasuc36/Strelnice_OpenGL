#pragma once

#include "pgr.h"

/**
 * \brief General functions (static methods to be more precise), that are static and require no other context.
 * 
 * This is separated from ServiceClass, because it is used accross whole application and would cause collisions, because of #includes
 */
static class GlobFunc
{
public:
	/**
	 * \brief Used to clamp lower values than min to min and higher than max to max. (int)
	 * 
	 * \param value input value
	 * \param min lower boundary
	 * \param max upper boundary
	 * \return clamped value
	 */
	static int Clamp(int value, const int min = 0, const int max = 1);

	/**
	 * \brief Used to clamp lower values than min to min and higher than max to max. (float)
	 *
	 * \param value input value
	 * \param min lower boundary
	 * \param max upper boundary
	 * \return clamped value
	 */
	static float Clamp(float value, const float min = 0.0f, const float max = 1.0f);

	/**
	 * \brief Used to clamp lower values than min to min and higher than max to max. (vec2)
	 *
	 * \param value input value
	 * \param min lower boundary
	 * \param max upper boundary
	 * \return clamped value
	 */
	static glm::vec2 Clamp(glm::vec2 value, const float min = 0.0f, const float max = 1.0f);

	/**
	 * \brief Used to clamp lower values than min to min and higher than max to max. (vec3)
	 *
	 * \param value input value
	 * \param min lower boundary
	 * \param max upper boundary
	 * \return clamped value
	 */
	static glm::vec3 Clamp(glm::vec3 value, const float min = 0.0f, const float max = 1.0f);



	/**
	 * \brief Used to get reminder of the previous value as New = Old % (max - min). (int)
	 *
	 * \param value input value
	 * \param min lower boundary
	 * \param max upper boundary
	 * \return moduled value
	 */
	static int Modulo(int value, const int min = 0, const int max = 1);

	/**
	 * \brief Used to get reminder of the previous value as New = Old % (max - min). (float)
	 *
	 * \param value input value
	 * \param min lower boundary
	 * \param max upper boundary
	 * \return moduled value
	 */
	static float Modulo(float value, const float min = 0.0f, const float max = 1.0f);

	/**
	 * \brief Used to get reminder of the previous value as New = Old % (max - min). (vec2)
	 *
	 * \param value input value
	 * \param min lower boundary
	 * \param max upper boundary
	 * \return moduled value
	 */
	static glm::vec2 Modulo(glm::vec2 value, const float min = 0.0f, const float max = 1.0f);

	/**
	 * \brief Used to get reminder of the previous value as New = Old % (max - min). (vec3)
	 *
	 * \param value input value
	 * \param min lower boundary
	 * \param max upper boundary
	 * \return moduled value
	 */
	static glm::vec3 Modulo(glm::vec3 value, const float min = 0.0f, const float max = 1.0f);
};

