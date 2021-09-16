#include "BoardPiece.h"

BoardPiece::BoardPiece()
{
}

BoardPiece::BoardPiece(bool XPiece)
{

	textureImagePath = (XPiece ? "res/XPiece.png" : "res/OPiece.png");

}

void BoardPiece::initializeBoardPieceData()
{

	boardPieceShader = new Shader("shaders/pieceShaders/pieceVertex.shader", "shaders/pieceShaders/pieceFragment.shader");

	puts("shader loaded");

	glm::vec4 color = { 0.82f, 0.71f, 0.55f, 1.0f };

	float vertices[] = {

		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f,//0
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,//1 
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,//2
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,//3

	};

	unsigned int indeces[] = {

		0, 1, 2,
		2, 3, 1

	};

	vertexArray = new VertexArray();

	indexBuffer = new IndexBuffer(*vertexArray, indeces, sizeof(vertices));
	vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));

	vertexBuffer->addAttribute(*vertexArray, 3, GL_FLOAT, 5 * sizeof(float), 0);
	vertexBuffer->addAttribute(*vertexArray, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

	puts("LOADING TEXTURE");
	texture = new Texture(textureImagePath);
	puts("DONE LOADING TEXTURE"); 

	boardPieceShader->use();
	boardPieceShader->setBool("winningPiece", false);
	boardPieceShader->setInt("tex", 0);
	boardPieceShader->setFloatFour("aCol", color.r, color.g, color.b, color.a);
	boardPieceShader->dontUse();

}

BoardPiece::~BoardPiece()
{

	puts("Deleting board piece"); 

	if (vertexArray != nullptr) {

		delete vertexArray;

	}

	if (vertexBuffer != nullptr) {

		delete vertexBuffer;

	}

	if (indexBuffer != nullptr) {

		delete indexBuffer;

	}

	if (boardPieceShader != nullptr) {

		delete boardPieceShader;

	}

	if (texture != nullptr) {

		delete texture; 

	}

}

void BoardPiece::draw(const glm::vec3& position, float scale, const glm::mat4& view, const glm::mat4& proj, float lerpFactor, bool isWinningPiece, const glm::vec4& color, float angle)
{

	boardPieceShader->use();
	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(scale, scale, 0.0f));

	glActiveTexture(GL_TEXTURE0);
	texture->bind(); 

	boardPieceShader->setMat4("model", model);
	boardPieceShader->setBool("winningPiece", isWinningPiece);
	boardPieceShader->setMat4("view", view);
	boardPieceShader->setMat4("proj", proj);
	boardPieceShader->setFloatFour("aCol", color.r, color.g, color.b, color.a);
	boardPieceShader->setFloat("lerpFactor", lerpFactor);

	vertexArray->bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	vertexArray->unbind();
	vertexBuffer->unbind();
	indexBuffer->unbind();
	boardPieceShader->dontUse();
	texture->unbind(); 
	
}
