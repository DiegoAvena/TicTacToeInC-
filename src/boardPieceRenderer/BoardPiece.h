/*

Creator: Diego Avena
Last Updated: 9/17/21

*/

#ifndef BOARD_PIECE_H
#define BOARD_PIECE_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shaderLoader/Shader.h"
#include "../graphics/IndexBuffer.h"
#include "../graphics/VertexArray.h"
#include "../graphics/VertexBuffer.h"
#include "../graphics/Texture2D.h"

/*

Contains all the functionality needed to render a board piece on the 
tic tac toe board, such as an X piece or an O piece

*/
class BoardPiece {

private:
	Shader* boardPieceShader; 

	VertexArray* vertexArray = nullptr;
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;

	Texture* texture = nullptr; 

protected:
	const char* textureImagePath; 
	BoardPiece(); 

public:
	BoardPiece(bool XPiece);
	void initializeBoardPieceData();
	~BoardPiece(); 
	void draw(const glm::vec3& position, float scale, const glm::mat4& view, const glm::mat4& proj, float lerpFactor, bool isWinningPiece = false, const glm::vec4& color = { 0.82f, 0.71f, 0.55f, 1.0f }, float angle = 0.0f);

};

#endif