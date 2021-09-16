#include "Texture2D.h"

Texture::Texture(const char* pathToImage)
{

	glGenTextures(1, &texture);
	
	bind(); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//load image in:
	stbi_set_flip_vertically_on_load(true);

	int width, height, numberOfColorChannels; 
	unsigned char* data = stbi_load(pathToImage, &width, &height, &numberOfColorChannels, 0); 

	if (data) {

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		puts("Texture was loaded!"); 

	}
	else {

		printf("Failed to load image for texture at path: %s\n", pathToImage);

	}

	stbi_image_free(data);
	unbind(); 

}

void Texture::bind()
{

	glBindTexture(GL_TEXTURE_2D, texture);

}

void Texture::unbind()
{

	glBindTexture(GL_TEXTURE_2D, 0);

}
