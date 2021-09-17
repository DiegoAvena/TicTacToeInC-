/*

Creator: Diego Avena
Last Updated: 9/17/21

*/

#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "VertexArray.h"

/*

Contains all the functionality needed to create and use 
an index buffer with OpenGL. An index buffer allows us to reuse 
vertex data from the vertex buffer, which can make memory usage more 
efficient, especially for larger objects

*/
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