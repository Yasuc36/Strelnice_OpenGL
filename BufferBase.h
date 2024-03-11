#pragma once

#include "pgr.h"

/**
 * \brief Serves as template for other classes (EBO, VAO, VBO). It just contains Index number
 */
class BufferBase
{
public:
	GLuint Index;  ///< Index used for shader location
};
