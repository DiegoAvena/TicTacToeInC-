#include "Square.h"

void Square::initializeSquareData()
{

	puts("Initializing shader"); 

	squareShader = new Shader("shaders/squareShaders/squareVertex.shader", "shaders/squareShaders/squareFragment.shader");

	puts("shader loaded"); 

	glm::vec4 color = { 0.82f, 0.71f, 0.55f, 1.0f };

	float vertices[] = {

		-0.5f,  0.5f, 0.0f, //0
		 0.5f,  0.5f, 0.0f, //1 
		-0.5f, -0.5f, 0.0f, //2
		 0.5f, -0.5f, 0.0f  //3

	};

	unsigned int indeces [] = {

		0, 1, 2,
		2, 3, 1

	};

	vertexArray = new VertexArray();

	indexBuffer = new IndexBuffer(*vertexArray, indeces, sizeof(vertices));
	vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));

	vertexBuffer->addAttribute(*vertexArray, 3, GL_FLOAT, 3 * sizeof(float), 0);
	
	squareShader->use();
	squareShader->setFloatFour("aCol", color.r, color.g, color.b, color.a);
	squareShader->dontUse();

}

Square::~Square() {

	puts("Deleting square");
	
	if (vertexArray != nullptr) {

		delete vertexArray;

	}

	if (vertexBuffer != nullptr) {

		delete vertexBuffer;

	}

	if (indexBuffer != nullptr) {

		delete indexBuffer; 

	}

	if (squareShader != nullptr) {

		delete squareShader;

	}

}

void Square::DrawSquare(const glm::vec3& position, float scale, const glm::vec3& rotation, const glm::mat4& view, const glm::mat4& proj, 
	const glm::vec4& color)
{

	squareShader->use(); 
	glm::mat4 model = glm::mat4(1.0f); 
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(scale, scale, 0.0f));

	squareShader->setMat4("model", model);
	squareShader->setMat4("view", view);
	squareShader->setMat4("proj", proj);
	squareShader->setFloatFour("aCol", color.r, color.g, color.b, color.a);

	vertexArray->bind(); 
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 

	GLenum err; 
	if ((err = glGetError()) != GL_NO_ERROR) {

		printf("OPENGL ERROR: %d\n", err);

	}

	vertexArray->unbind();
	vertexBuffer->unbind();
	indexBuffer->unbind();
	squareShader->dontUse(); 

}
