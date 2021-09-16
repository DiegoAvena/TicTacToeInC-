#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <cstdio>

#include "../stb_image.h"

class Texture {

private:
	unsigned int texture; 

public:
	Texture(const char* pathToImage); 
	void bind();
	void unbind(); 

};

#endif 