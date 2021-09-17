/*

Creator: Diego Avena
Last Updated: 9/17/21

*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <cstdio>

#include "../stb_image.h"

/*

Contains the functionality needed to load up 
textures for use with openGL.

*/
class Texture {

private:
	unsigned int texture; 

public:
	Texture(const char* pathToImage); 
	void bind();
	void unbind(); 

};

#endif 