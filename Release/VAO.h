#pragma once

#include "pgr.h"
#include "BufferBase.h"

/**
 * \brief VAO - Vertex array class for connectinc VBO and EBO. Contains methods to connect needed buffers.
 */
class VAO : public BufferBase
{
public:
	GLuint Vbo;  ///< Index of corresponding VBO
	GLuint Ebo;  ///< Index of corresponding EBO



	//! Constructor
	VAO();



	/**
	* \brief Connects only VBO to VAO (When EBO is unavaiable).
	* 
	* \param vbo index of Vbo 
	*/
	void ConnectBuffers(GLuint vbo);

	/**
	* \brief Connects both VBO and EBO
	*
	* \param vbo index of Vbo
	*/
	void ConnectBuffers(GLuint vbo, GLuint ebo);
};

