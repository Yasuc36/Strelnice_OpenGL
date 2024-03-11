#include "EBO.h""

EBO::EBO()
{
	glGenBuffers(1, &Index);  // Create 1 buffer and save its index
    CHECK_GL_ERROR();
}

void EBO::SetData(const std::vector<unsigned int>& indices)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);  // Fill buffer with indicies
    CHECK_GL_ERROR();
}

void EBO::LoadObject(const aiMesh* mesh)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Index);
    
    // copy all mesh faces into one big array (assimp supports faces with ordinary number of vertices, we use only 3 -> triangles)
    unsigned int* indices = new unsigned int[mesh->mNumFaces * 3];
    for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
        indices[f * 3 + 0] = mesh->mFaces[f].mIndices[0];
        indices[f * 3 + 1] = mesh->mFaces[f].mIndices[1];
        indices[f * 3 + 2] = mesh->mFaces[f].mIndices[2];
    }

    // copy our temporary index array to OpenGL and free the array
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int) * mesh->mNumFaces, indices, GL_STATIC_DRAW);

    CHECK_GL_ERROR();

    // remove temporary array
    delete[] indices;
}
