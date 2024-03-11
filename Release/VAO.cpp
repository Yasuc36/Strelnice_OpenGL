#include "VAO.h"

VAO::VAO()
{
	Vbo = -1;
	Ebo = -1;
	glGenVertexArrays(1, &Index);
	CHECK_GL_ERROR();
}

void VAO::ConnectBuffers(GLuint vbo)
{
	Vbo = vbo;
	glBindVertexArray(Index);
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);  // bind our Vertex Buffer Object (vertices) to VAO
	glBindVertexArray(0);
	CHECK_GL_ERROR();
}

void VAO::ConnectBuffers(GLuint vbo, GLuint ebo)
{
	Vbo = vbo;
	Ebo = ebo;
	glBindVertexArray(Index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);  // bind our element array buffer (indices) to vao
	glBindBuffer(GL_ARRAY_BUFFER, Vbo);  // bind our Vertex Buffer Object (vertices) to VAO
	glBindVertexArray(0);
	CHECK_GL_ERROR();
}