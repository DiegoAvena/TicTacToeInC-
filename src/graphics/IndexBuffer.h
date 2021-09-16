#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "VertexArray.h"

class IndexBuffer {

private:
	unsigned int indexBuffer; 
	IndexBuffer(); 

public:
	IndexBuffer(VertexArray& va, unsigned int* indeces, size_t size); 
	void bind(); 
	void unbind(); 

};

#endif