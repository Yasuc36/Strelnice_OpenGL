#pragma once

#include "pgr.h"
#include "BufferBase.h"

/**
 * \brief EBO - Element array buffer class. Contains methods to create needed EBO (GL_ELEMENT_ARRAY_BUFFER).
 */
class EBO : public BufferBase
{
public:
	//! \brief Constructor
	EBO();


	/** 
	* \brief Used to fill Buffer with data specified in vector
	* 
	* \param indices vector of all verices (3*uint(vertex indices) per triangle)
	*/
	void SetData(const std::vector<unsigned int> & indices);

	/**
	* \brief Used to fill Buffer with data specified in aiMesh filled by Assimp
	*
	* \param mesh array of all loaded data from Assimp. Used to get indices of loaded file.
	*/
	void LoadObject(const aiMesh* mesh);
};

