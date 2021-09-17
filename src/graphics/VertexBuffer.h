/*

Creator: Diego Avena
Last Updated: 9/17/21

*/

#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "VertexArray.h"

/*

Contains everything needed to create a vertex buffer, which stores all our vertex 
data so that the GPU can use it to draw shapes. 

*/
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