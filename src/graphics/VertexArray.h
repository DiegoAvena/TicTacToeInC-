#ifndef VERTEX_ARRAY_H 
#define VERTEX_ARRAY_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

class VertexArray {

private:
	unsigned int vertexArray;

public:
	VertexArray();

	void bind(); 
	void unbind();

};

#endif
