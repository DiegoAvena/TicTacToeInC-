#ifndef SHADER_H 
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include <fstream>
#include <sstream>
#include <cstdio>

//#include <iostream>

class Shader {

public:
	unsigned int ID; 

	Shader(); 
	Shader(const char* vertexPath, const char* fragmentPath);

	void use(); 
	void dontUse(); 

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const; 
	void setFloat(const std::string& name, float value) const; 
	void setFloatTwo(const std::string& name, float valueOne, float valueTwo) const; 
	void setFloatThree(const std::string& name, float valueOne, float valueTwo, float valueThree) const;
	void setFloatFour(const std::string& name, float valueOne, float valueTwo, float valueThree, float valueFour) const;
	void setMat4(const std::string& name, glm::mat4 trans);

	//unsigned int compileShader(GLenum shaderType, const char* sourceCode);

};

#endif