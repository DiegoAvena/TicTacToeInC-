#ifndef SQUARE_H
#define SQUARE_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shaderLoader/Shader.h"
#include "../graphics/IndexBuffer.h"
#include "../graphics/VertexArray.h"
#include "../graphics/VertexBuffer.h"

class Square {

private:
	Shader* squareShader = nullptr; 

	VertexArray* vertexArray = nullptr; 
	VertexBuffer* vertexBuffer = nullptr; 
	IndexBuffer* indexBuffer = nullptr; 

public:
	void initializeSquareData();
	~Square(); 
	void DrawSquare(const glm::vec3& position, float scale, const glm::vec3& rotation, const glm::mat4& view, const glm::mat4& proj, const glm::vec4& color = { 0.82f, 0.71f, 0.55f, 1.0f });

};

#endif
