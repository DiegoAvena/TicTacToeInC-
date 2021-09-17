/*

Creator: Diego Avena
Last Updated: 9/17/21

*/

#ifndef TIC_TAC_TOE_MANAGER_H
#define TIC_TAC_TOE_MANAGER_H 

#include "BoardGameBase.h"
#include "squareRenderer/Square.h"
#include "boardPieceRenderer/BoardPiece.h"
#include "gameOverTitleRenderer/GameOverCard.h"

#include <map>

/*

Contains all the functionality needed for an 
implementation of TicTacToe, using OpenGL for 
graphics rendering

*/
class TicTacToeManager : public BoardGameBase {

public:
	TicTacToeManager(); 
	~TicTacToeManager(); 

protected:
	void update(GLFWwindow* window) override; 
	void draw(GLFWwindow* window) override; 
	void initializeGameData() override; 
	void resetGameData() override;

	bool checkIfGameIsOver() override; 

private:

	//For the board BG
	Square* square = nullptr; 

	//for the pieces that get rendered on the boardBG
	BoardPiece* XPiece = nullptr; 
	BoardPiece* OPiece = nullptr; 

	/*
	
	For optimization, the 3 different card variants are never loaded all at once, because 
	only 1 ever shows up at the end of a match, so I just pick and load the correct 1 when
	the match ends
	
	*/
	GameOverCard* gameOverCard = nullptr; 

	int initialWidth; 
	int initialHeight; 

	/*
	
	for a little animation effect when a grid is selected by either the AI or player
	
	each grid will need to keep track of its own timer when it is transforming, so this is what 
	the hashmap is for. It stores the time elapsed in the covnersion for that grid, and the key 
	is the index that grid is at on the board

	*/
	const float CHANGETIME = 0.5f; 
	std::map<int, float> transformingPieces; 

	//Defines the different states a grid on the tic tac toe board can be in.
	enum GridState {

		X,
		X_CONVERTING,
		O,
		O_CONVERTING,
		NONE,
		HOVERING

	};

	//tracks who won
	GridState winner = NONE; 

	//tracks on which row or col the win was detected
	unsigned int rowOrColWon; 

	//defines the different ways a game can end
	enum GameOverType {

		ROW,
		COL,
		TOP_LEFT_TO_BOTTOM_RIGHT_DIAGONAL,
		TOP_RIGHT_TO_BOTTOM_LEFT_DIAGONAL,
		TIE

	};

	//for checking if game is over
	GameOverType gameOverType;
	unsigned int numberOfGridsFilled = 0; 
	
	//for the reset game effect
	float currentRotationAngle = 0.0f;
	const float MAXROTATIONANGLE = 90.0f; 

	//for counting down to resetting the game: 
	float timeElapsed = 0.0f; 
	const float RESETCOUNTER = 3.5f; 

	//for displaying game over message to player: 
	const float DELAYBEFOREDISPLAYINGGAMEOVERMESSAGETOPLAYER = RESETCOUNTER / 2.0f;

	//AI move countdown: 
	const float AITHINKTIME = 1.2f; 

	//represents the current state of the game board
	GridState theGrid[9] = {

		NONE, NONE, NONE,
		NONE, NONE, NONE,
		NONE, NONE, NONE

	};

	//tracks whose turn it is
	GridState currentPlayer = X;

	//tracks which character the player is
	GridState player = X; 

	//rendering and chacking grid positions
	float scaleFactor = 0.0f;
	float boardSize = 0.0f;
	float gridOffset = 0.0f; 
	float gridSize = 0.0f; 

private:

	//helper method for checking if player is hovering over a grid
	bool checkIfPlayerHoveringOverCurrentGrid(float xPos, float yPos); 

	//helper method for checking if there was a winner in the given board
	bool checkForWinner(const GridState* grid);

	//helper method for checking if current grid is converting to a specific character
	bool checkIfGridConvertingForCharacter(const GridState* grid, const int& index, const GridState& characterToCheckFor);
	
	//Helper method used to allow the grids to gradually convert to a character when their state is *_CONVERTING
	float obtainLerpFactorForConversionEffect(int row, int col, GridState pieceToChange);

	//used by AI to determine the next move to make
	int getMoveWithMinMax(const GridState grid[9], const GridState& playerToCheck, int& move);


};

#endif