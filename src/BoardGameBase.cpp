#include "BoardGameBase.h"
#include "squareRenderer/Square.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexArray.h"

//define the static vars
unsigned int BoardGameBase::screenHeight = 1024; 
unsigned int BoardGameBase::screenWidth = 1024; 

float BoardGameBase::mouseX = 0.0f;
float BoardGameBase::mouseY = 0.0f;
bool BoardGameBase::madeFirstMouseMovement = false;

//called when the window gets resized
void resize(GLFWwindow* window, int width, int height) {

	BoardGameBase::screenHeight = height; 
	BoardGameBase::screenWidth = width; 

	glViewport(0, 0, width, height);

}

//called when the mouse moves on the window
void onMouseMoved(GLFWwindow* window, double xPos, double yPos) {

	BoardGameBase::mouseX = (float)xPos; 
	BoardGameBase::mouseY = (float)yPos; 

	//need to offset the mouse x so it matches the world coord space: 
	BoardGameBase::mouseX -= ((float)BoardGameBase::screenWidth / 2.0f);
	BoardGameBase::mouseY = ((float)BoardGameBase::screenHeight / 2.0f) - BoardGameBase::mouseY;

	//printf("Mouse Pos: < %f, %f >\n", BoardGameBase::mouseX, BoardGameBase::mouseY);
	BoardGameBase::madeFirstMouseMovement = true; 

}

BoardGameBase::BoardGameBase() {

	gameName = "BoardGame";
	backgroundColor = { 0.46f, 0.51f, 0.36f, 1.0f };

}

void BoardGameBase::manageGame()
{

	//initialize glfw:
	glfwInit(); 

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
#endif

	//create the window
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, gameName, NULL, NULL);
	if (window == NULL) {

		puts("Failed to create window!"); 
		glfwTerminate(); 
		return;

	}

	glfwMakeContextCurrent(window);

	//load up glad: 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

		puts("Failed to load up GLAD"); 
		return;

	}

	//create viewport: 
	glViewport(0, 0, screenWidth, screenHeight);

	//register callbacks: 
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, onMouseMoved);

	initializeGameData(); 
	
	//the game loop: 
	while (!glfwWindowShouldClose(window)) {

		//delta time is used to provide consistent timing on all devices
		float currentTime = glfwGetTime(); 
		deltaTime = currentTime - timeLastFrameStarted; 
		timeLastFrameStarted = currentTime; 

		manageInput(window);

		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT);

		draw(window); //handle drawing here 
		update(window); //handle game logic here
		
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate(); 

}

//manage user input here
void BoardGameBase::manageInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

		glfwSetWindowShouldClose(window, true);

	}

	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) && !mouseButtonPressed) {

		mouseButtonPressed = true; 

	}
	else if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) && mouseButtonPressed) {

		mouseButtonPressed = false; 

	}
}

void BoardGameBase::resetGameData()
{

	displayGameOverCard = false;
	backgroundColor = { 0.46f, 0.51f, 0.36f, 1.0f };
	gameOver = false; 
	resetGame = false; 

}
