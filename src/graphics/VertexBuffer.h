#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "VertexArray.h"

class VertexBuffer {

private:
	unsigned int currentAttributeIndex; 
	unsigned int vertexBuffer; 
	VertexBuffer(); 

public:
	VertexBuffer(float* vertices, size_t size);
	void bind(); 
	void unbind(); 
	void addAttribute(VertexArray& va, int size, GLenum type, int stride, int offset);

};

#endif