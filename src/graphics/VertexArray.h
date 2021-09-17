/*

Creator: Diego Avena
Last Updated: 9/17/21

*/

#ifndef VERTEX_ARRAY_H 
#define VERTEX_ARRAY_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

/*

Contains the functionality needed to create a vertex
array (which stores index buffer binding and vertex attribute settings)
for use with OpenGL

*/
class VertexArray {

private:
	unsigned int vertexArray;

public:
	VertexArray();

	void bind(); 
	void unbind();

};

#endif
