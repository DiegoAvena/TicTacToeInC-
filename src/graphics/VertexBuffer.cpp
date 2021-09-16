#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(float* vertices, size_t size)
{

	currentAttributeIndex = 0; 

	glGenBuffers(1, &vertexBuffer); 
	
	bind(); 

	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	unbind(); 

}

void VertexBuffer::bind()
{

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

}

void VertexBuffer::unbind()
{

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void VertexBuffer::addAttribute(VertexArray& va, int size, GLenum type, int stride, int offset)
{

	va.bind(); 
	bind(); 
	glVertexAttribPointer(currentAttributeIndex, size, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(currentAttributeIndex);
	currentAttributeIndex++;
	va.unbind(); 
	unbind(); 

}
