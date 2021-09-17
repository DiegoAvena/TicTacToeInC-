/*

Creator: Diego Avena
Last Updated: 9/17/21

*/

#ifndef BOARD_GAME_H
#define BOARD_GAME_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdio>
#include "shaderLoader/Shader.h"

/*

A base class for turn based games, such as Tic Tac Toe, 
Chess, Checkers, etc.

*/
class BoardGameBase {

public:
	void manageGame(); //call this to launch the game
	BoardGameBase(); 

	/*
	
	The mouseX and mouseY position are inaccurate until 
	the user actually moves the mouse on the window, so this 
	flag should be used to prevent the use of mouseX and mouseY 
	until the user has moved the mouse at least once
	
	*/
	static bool madeFirstMouseMovement; 

	//the window and viewport height and width
	static unsigned int screenWidth;
	static unsigned int screenHeight;

	//these track mouse position of player on window
	static float mouseX; 
	static float mouseY; 

protected:
	virtual void draw(GLFWwindow* window) = 0; //drawing logic goes here
	virtual void update(GLFWwindow* window) = 0; //game logic goes here
	virtual void initializeGameData() = 0; //place more specific game data to initialize in here
	virtual void manageInput(GLFWwindow* window); //launches all glfw and opengl things, and begin the game loop
	virtual bool checkIfGameIsOver() = 0; //put game over logic in here
	virtual void resetGameData(); //should reset the game for another match 

protected:
	const char* gameName; //the title of the window
	bool mouseButtonPressed = false; //whether or not the mouse button was pressed
	
	//used to provide consistent timing on all devices
	float deltaTime = 0.0f; 
	float timeLastFrameStarted = 0.0f; 

	bool resetGame = false; //indicates that the game needs to reset for another match
	bool gameOver = false; //indicates that the current match is over
	
	bool displayGameOverCard = false; //indicates that the game over card with a message needs to be shown

	glm::vec4 backgroundColor; //the clear color of the screen

};

#endif
