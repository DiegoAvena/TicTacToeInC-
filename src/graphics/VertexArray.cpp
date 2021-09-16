#include "VertexArray.h"

VertexArray::VertexArray()
{

	glGenVertexArrays(1, &vertexArray);

}

void VertexArray::bind()
{

	glBindVertexArray(vertexArray);

}

void VertexArray::unbind()
{

	glBindVertexArray(0);

}
