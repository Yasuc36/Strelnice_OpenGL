#include "VBO.h"

VBO::VBO()
{
	glGenBuffers(1, &Index); // Create 1 buffer and save its index
    CHECK_GL_ERROR();
}

void VBO::SetData(const std::vector<float> & vertices)
{
    glBindBuffer(GL_ARRAY_BUFFER, Index);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW); // works
    CHECK_GL_ERROR();
}

void VBO::LoadObject(const aiMesh* mesh)
{
    glBindBuffer(GL_ARRAY_BUFFER, Index);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float) * mesh->mNumVertices, 0, GL_STATIC_DRAW); // allocate memory for vertices, normals, and texture coordinates
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float) * mesh->mNumVertices, mesh->mVertices); // store all vertices
	glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float) * mesh->mNumVertices, 3 * sizeof(float) * mesh->mNumVertices, mesh->mNormals); // store all normals


	// Textures
    float* textureCoords = new float[2 * mesh->mNumVertices];  // 2 floats per vertex
    float* currentTextureCoord = textureCoords;

    // Copy texture coordinates
    aiVector3D vect;
    if (mesh->HasTextureCoords(0)) // we use 2D textures with 2 coordinates and ignore the third coordinate
    {
        for (unsigned int idx = 0; idx < mesh->mNumVertices; idx++) 
        {
            vect = (mesh->mTextureCoords[0])[idx];
            *currentTextureCoord++ = vect.x;
            *currentTextureCoord++ = vect.y;
        }
    }    
    glBufferSubData(GL_ARRAY_BUFFER, 6 * sizeof(float) * mesh->mNumVertices, 2 * sizeof(float) * mesh->mNumVertices, textureCoords); // store all texture coordinates
    CHECK_GL_ERROR();
}