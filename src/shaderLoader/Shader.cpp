#include "Shader.h"

Shader::Shader()
{
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	//1: retrieve the vertex/fragment source code from file paths 
	std::string vertexCode; 
	std::string fragmentCode; 

	//the input streams that will be used to read from the files
	std::ifstream vertexShaderFile; 
	std::ifstream fragmentShaderFile; 

	//make sure ifstream objects can throw exceptions 
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit); 

	try {

		//open files 
		vertexShaderFile.open(vertexPath); 
		fragmentShaderFile.open(fragmentPath);

		std::stringstream vertexShaderStream, fragmentShaderStream; 

		//read file contents into the streams: 
		vertexShaderStream << vertexShaderFile.rdbuf(); 
		fragmentShaderStream << fragmentShaderFile.rdbuf(); 

		//close file handlers: 
		vertexShaderFile.close(); 
		fragmentShaderFile.close(); 

		//convert streams into strings: 
		vertexCode = vertexShaderStream.str(); 
		fragmentCode = fragmentShaderStream.str(); 

		puts("Shader source code has been loaded!");

	}
	catch (...) {

		puts("Error: shader file could not be opened");

	}

	const char* vertShaderCode = vertexCode.c_str(); 
	const char* fragShaderCode = fragmentCode.c_str(); 

	//compile the shaders now: 
	auto compileShader = [](GLenum shaderType, const char* sourceCode) -> unsigned int {

		printf("Compiling %s\n", (shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader"));
		unsigned int shader = glCreateShader(shaderType);

		glShaderSource(shader, 1, &sourceCode, NULL);
		glCompileShader(shader);

		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {

			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			printf("Failed to compile %s with error: %s\n", (shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader"), infoLog);
			return 0;

		}

		printf("%s compiled!\n", (shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader"));

		return shader;

	}; 

	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertShaderCode); 
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragShaderCode); 

	//create the shader program now: 
	ID = glCreateProgram(); 
	glAttachShader(ID, vertexShader); 
	glAttachShader(ID, fragmentShader); 
	glLinkProgram(ID); 

	int success; 
	char infoLog[512]; 
	glGetProgramiv(ID, GL_LINK_STATUS, &success); 
	if (!success) {

		glGetProgramInfoLog(ID, 512, NULL, infoLog); 
		printf("Failed to link shader program with error of: %s\n", infoLog);

	}

	glDeleteShader(vertexShader); 
	glDeleteShader(fragmentShader);

}

void Shader::use()
{

	glUseProgram(ID); 

}

void Shader::dontUse()
{

	glUseProgram(0); 

}

void Shader::setBool(const std::string& name, bool value) const
{

	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);

}

void Shader::setInt(const std::string& name, int value) const
{

	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);

}

void Shader::setFloat(const std::string& name, float value) const
{

	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);

}

void Shader::setFloatTwo(const std::string& name, float valueOne, float valueTwo) const
{

	glUniform2f(glGetUniformLocation(ID, name.c_str()), valueOne, valueTwo);

}

void Shader::setFloatThree(const std::string& name, float valueOne, float valueTwo, float valueThree) const
{

	glUniform3f(glGetUniformLocation(ID, name.c_str()), valueOne, valueTwo, valueThree);

}

void Shader::setFloatFour(const std::string& name, float valueOne, float valueTwo, float valueThree, float valueFour) const
{

	glUniform4f(glGetUniformLocation(ID, name.c_str()), valueOne, valueTwo, valueThree, valueFour);

}

void Shader::setMat4(const std::string& name, glm::mat4 trans)
{

	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));

}

/*unsigned int Shader::compileShader(GLenum shaderType, const char* sourceCode) {

	printf("Compiling %s\n", (shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader"));
	unsigned int shader = glCreateShader(shaderType);
	puts("TEST");

	glShaderSource(shader, 1, &sourceCode, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {

		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("Failed to compile %s with error: %s\n", (shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader"), infoLog);
		return 0;

	}

	printf("%s compiled!\n", (shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader"));

	return shader;

} */
