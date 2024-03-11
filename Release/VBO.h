#pragma once

#include "pgr.h"
#include "BufferBase.h"

/**
 * \brief VBO - Vertex buffer class. Contains methods to create needed VBO (GL_ARRAY_BUFFER).
 */
class VBO : public BufferBase
{
public:
	//! \brief Constructor
	VBO();



	/**
	* \brief Used to fill Buffer with data specified in vector
	*
	* \param indices vector of all verices (3*uint(vertex indices) per triangle)
	*/
	void SetData(const std::vector<float> & vertices);

	/**
	* \brief Used to fill Buffer with data specified in aiMesh filled by Assimp
	*
	* \param mesh array of all loaded data from Assimp. Used to get indices of loaded file.
	*/
	void LoadObject(const aiMesh* mesh);
};

