#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(VertexArray& va, unsigned int* indeces, size_t size)
{

	va.bind(); 

	glGenBuffers(1, &indexBuffer);

	bind(); 

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indeces, GL_STATIC_DRAW);

	va.unbind(); 
	unbind(); 

}

void IndexBuffer::bind()
{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

}

void IndexBuffer::unbind()
{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
