#include "TicTacToeManager.h"

TicTacToeManager::TicTacToeManager()
{

	gameName = "Tic Tac Toe in C++!";
	initialWidth = screenWidth; 
	initialHeight = screenHeight; 

}

TicTacToeManager::~TicTacToeManager() {

	if (square != nullptr) {

		delete square;

	}

	if (XPiece != nullptr) {

		delete XPiece; 

	}

	if (OPiece != nullptr) {

		delete OPiece;

	}

	if (gameOverCard != nullptr) {

		delete gameOverCard; 
		gameOverCard = nullptr; 

	}

}

void TicTacToeManager::initializeGameData() {

	square = new Square();
	square->initializeSquareData();

	XPiece = new BoardPiece(true);
	XPiece->initializeBoardPieceData();

	OPiece = new BoardPiece(false); 
	OPiece->initializeBoardPieceData();

}

bool TicTacToeManager::checkIfGameIsOver()
{

	if (checkForWinner(theGrid)) {

		return true;

	}

	if (numberOfGridsFilled >= 9) {

		//was a tie
		puts("TIE GAME");
		winner = NONE;
		gameOverType = TIE;
		return true;

	}

	return false; 

}

bool TicTacToeManager::checkIfPlayerHoveringOverCurrentGrid(float xPos, float yPos) {

	if ((mouseX < (xPos + (gridSize / 2.0f))) && (mouseX >(xPos - (gridSize / 2.0f)))) {

		if ((mouseY < (yPos + (gridSize / 2.0f)) && (mouseY > (yPos - (gridSize / 2.0f))))) {

			return true; 

		} 

	}

	return false; 

}

float TicTacToeManager::obtainLerpFactorForConversionEffect(int row, int col, GridState pieceToChange)
{

	int key = (row * 3) + col;
	float lerpFactor = (glfwGetTime() - transformingPieces[key]) / CHANGETIME;
	if (lerpFactor > 0.98f) {

		lerpFactor = 1.0f;
		transformingPieces.erase(key);
		theGrid[key] = pieceToChange;

	}

	return lerpFactor; 

}

/*

A grid that contains a value of O_CONVERTING should be treated as being equal to an O, because 
that grid is destined to become an O anyway. 

A grid that contains a value of X_CONVERTING should also be treated as being equal to an X, because 
that grid is destined to become an X anyway. 

This method insures this relation is maintained

*/
bool TicTacToeManager::checkIfGridConvertingForCharacter(const GridState* grid, const int& index, const GridState& characterToCheckFor) {

	return (grid[index] == O_CONVERTING && characterToCheckFor == O) 
		|| (grid[index] == O && characterToCheckFor == O_CONVERTING) 
		|| (grid[index] == X_CONVERTING && characterToCheckFor == X) 
		|| (grid[index] == X && characterToCheckFor == X_CONVERTING);

}

bool TicTacToeManager::checkForWinner(const GridState* grid)
{

	//check all horizontals
	for (int row = 0; row < 3; ++row) {

		GridState pieceWhoMightControlThisRow = NONE;
		bool rowWon = true;

		for (int col = 0; col < 3; ++col) {

			unsigned int index = (row * 3) + col;
			if (pieceWhoMightControlThisRow == NONE) {

				pieceWhoMightControlThisRow = grid[index];

			}

			if ((pieceWhoMightControlThisRow != grid[index] && !checkIfGridConvertingForCharacter(grid, index, pieceWhoMightControlThisRow)) || grid[index] == NONE) {

				rowWon = false;
				break;

			}

		}

		if (rowWon) {

			rowOrColWon = row;
			gameOverType = ROW;
			winner = pieceWhoMightControlThisRow;
			return true;

		}

	}

	//check all verticals: 
	for (int col = 0; col < 3; ++col) {

		GridState pieceWhoMightControlThisRow = NONE;
		bool colWon = true;

		for (int row = 0; row < 3; ++row) {

			unsigned int index = (row * 3) + col;
			if (pieceWhoMightControlThisRow == NONE) {

				pieceWhoMightControlThisRow = grid[index];

			}

			if ((pieceWhoMightControlThisRow != grid[index] && !checkIfGridConvertingForCharacter(grid, index, pieceWhoMightControlThisRow)) || grid[index] == NONE) {

				colWon = false;
				break;

			}

		}

		if (colWon) {

			rowOrColWon = col;
			winner = pieceWhoMightControlThisRow;
			gameOverType = COL;

			return true;

		}

	}

	//check all diagonals: 
	bool diagonalWon = true;
	GridState pieceWhoMightControlThisDiagonal = NONE;

	//top left to bottom right diagonal
	for (int i = 0; i < 3; i++) {

		unsigned int index = (i * 3) + i;

		if (pieceWhoMightControlThisDiagonal == NONE) {

			pieceWhoMightControlThisDiagonal = grid[index];

		}

		if ((pieceWhoMightControlThisDiagonal != grid[index] && !checkIfGridConvertingForCharacter(grid, index, pieceWhoMightControlThisDiagonal)) || grid[index] == NONE) {

			diagonalWon = false;
			break;

		}

	}

	if (diagonalWon) {

		gameOverType = TOP_LEFT_TO_BOTTOM_RIGHT_DIAGONAL;
		winner = pieceWhoMightControlThisDiagonal;
		return true;

	}

	diagonalWon = true;
	pieceWhoMightControlThisDiagonal = NONE;

	//bottom left to top right diagonal
	int row = 2;
	int col = 0;
	for (int i = 0; i < 3; i++) {

		int index = (row * 3) + col;

		if (pieceWhoMightControlThisDiagonal == NONE) {

			pieceWhoMightControlThisDiagonal = grid[index];

		}

		if ((pieceWhoMightControlThisDiagonal != grid[index] && !checkIfGridConvertingForCharacter(grid, index, pieceWhoMightControlThisDiagonal)) || grid[index] == NONE) {

			diagonalWon = false;
			break;

		}

		row--;
		col++;

	}

	if (diagonalWon) {

		winner = pieceWhoMightControlThisDiagonal;
		gameOverType = TOP_RIGHT_TO_BOTTOM_LEFT_DIAGONAL;
		return true;

	}

	return false;

}

/*

The algorithm behind this is minmax. The game of Tic Tac Toe, like other 
turn based games, is really about searching through all the different game 
states and picking the most favorable one; this algorithm, being a search 
algorithm, lends itself nicely to this. 

The basic idea is you have 2 players: the AI (who we will call Max) and the player (who we 
will call Min). Max always seeks to maximize the score, while min always seeks to minimize the 
score.

For a given board configuration, we construct a tree, called a decision tree, containing all of the possible configurations the 
game can go toward for each move the AI makes. We then attach scores to each node using some type of heuristic 
that may be unique to each game. For tic tac toe, our hearistic was that if a given configuration is a loss for the AI, score that 
board as -1, else score it as +1. After this, we iterate through each node in the decision tree, and if current turn is MAX, we pick the move
that gives a higher score (so we would tend toward moves that give us a +1 score in our tic tac toe game) and if current turn is MIN, we pick 
the move that gives a lower score (so we would tend toward moves that give us a -1 score). 

See these sources for more information on MinMax: 
https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/

Also see this, which served as reference for the implementation of minmax below: 
https://gsurma.medium.com/tic-tac-toe-creating-unbeatable-ai-with-minimax-algorithm-8af9e52c1e7d#14e6

As this source states, a nice way to think of minmax is that is like the human though process of saying "If I did this, then my 
opponent can make the following moves, and those would allow me to potentially win or tie, so let me make that move..."

*/
int TicTacToeManager::getMoveWithMinMax(const GridState grid[9], const GridState& playerToCheck, int& move)
{
	
	if (checkForWinner(grid)) {

		return (winner == player ? -1 : 1) * (playerToCheck == player ? -1 : 1);

	}

	int score = -2; 
	int newMove = -1;

	//loop through all possible configurations for current player: 
	for (int i = 0; i < 9; ++i) {

		if (grid[i] == NONE) {

			//COPY GRID SO AS NOT TO AFFECT CURRENT GRID:
			GridState gridCopy[9]; 
			for (int b = 0; b < 9; b++) {

				gridCopy[b] = grid[b];

			}
			gridCopy[i] = playerToCheck;

			int potentialScore = -getMoveWithMinMax(gridCopy, (playerToCheck == X ? O : X), newMove);
			if (potentialScore > score) {

				score = potentialScore; 
				move = i;

			}

		}		

	} 
	
	if (move == -1) {

		//the current board is a tied game
		return 0; 

	}

	return score; 

}

//handle game logic here
void TicTacToeManager::update(GLFWwindow* window)
{

	if (!madeFirstMouseMovement) {

		return;

	}

	if (!gameOver && !resetGame) {

		if (currentPlayer == player) {

			float currentYPos = (boardSize / 3) - (10 * scaleFactor);

			//record the grid the player is hovering over so if they click on it, it can be marked
			int selectedRow = 0;
			int selectedCol = 0;

			bool gridPlayerHoveringOverFound = false;

			//check which grid player is hovering over: 
			for (int row = 0; row < 3; ++row) {

				float currentXPos = -(boardSize / 3) + (10 * scaleFactor);

				for (int col = 0; col < 3; col++) {

					if (checkIfPlayerHoveringOverCurrentGrid(currentXPos, currentYPos)) {

						//player hovering over this grid, mark it hovered so it can be colored in accordingly
						if (theGrid[(row * 3) + col] == NONE) {

							theGrid[(row * 3) + col] = HOVERING;
							gridPlayerHoveringOverFound = true;
							selectedRow = row;
							selectedCol = col;

						}

						if (theGrid[(row * 3) + col] == HOVERING) {

							gridPlayerHoveringOverFound = true;
							selectedRow = row;
							selectedCol = col;

						}

					}
					else {

						//player not hovering over this grid
						if (theGrid[(row * 3) + col] == HOVERING) {

							theGrid[(row * 3) + col] = NONE;

						}

					}

					currentXPos += gridOffset;

				}

				currentYPos -= gridOffset;

			}

			//check if player clicking on a grid they are hovering over so it can be filled in for them:
			if (mouseButtonPressed && (theGrid[(selectedRow * 3) + selectedCol] == HOVERING)) {

				numberOfGridsFilled++;

				theGrid[(selectedRow * 3) + selectedCol] = X_CONVERTING;
				transformingPieces[(selectedRow * 3) + selectedCol] = glfwGetTime();

				currentPlayer = O; 

			}

		}
		else {

			//AI's turn to go
			timeElapsed += deltaTime;
			if (timeElapsed > AITHINKTIME) {

				timeElapsed = 0.0f; 
				int indexToMoveOn = 0;
				getMoveWithMinMax(theGrid, O, indexToMoveOn);
				theGrid[indexToMoveOn] = O_CONVERTING;
				transformingPieces[indexToMoveOn] = glfwGetTime();

				numberOfGridsFilled++;

				currentPlayer = player;

			}

		}

		gameOver = checkIfGameIsOver();
		
	}
	else if (!resetGame) {

		//countdown until when the game should automatically reset: 
		timeElapsed += deltaTime; 
		resetGame = (timeElapsed >= RESETCOUNTER ? true : false); 
		gameOver = !resetGame; 

		//the gameover card should show up halfway through the reset timer
		displayGameOverCard = (timeElapsed >= DELAYBEFOREDISPLAYINGGAMEOVERMESSAGETOPLAYER ? true : false);

		if (resetGame) {

			backgroundColor = { 0.46f, 0.51f, 0.36f, 1.0f };
			displayGameOverCard = false; 

			timeElapsed = 0.0f; 

		}

	}
	else {
		
		//reset the board
		currentRotationAngle += (65.0f * deltaTime);
		if (currentRotationAngle > MAXROTATIONANGLE) {

			resetGameData(); 

		}

	}

}

//reset all game data for another match
void TicTacToeManager::resetGameData() {

	BoardGameBase::resetGameData(); 

	//loop through grid and clear it out: 
	for (int i = 0; i < 9; i++) {

		theGrid[i] = NONE; 

	}

	timeElapsed = 0.0f; 
	currentRotationAngle = 0.0f; 
	transformingPieces.clear(); 
	
	currentPlayer = X; 

	numberOfGridsFilled = 0; 
	winner = NONE; 

}

//handle drawing here
void TicTacToeManager::draw(GLFWwindow* window)
{

	//starts the camera off at 0.0
	glm::mat4 view = glm::mat4(1.0f); 
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
	
	//defines a border for the cam that goes from -screenwidth/2 to screenwidth / 2, with 0.0 at the center
	glm::mat4 proj = glm::mat4(1.0f); 
	proj = glm::ortho(-(float)screenWidth/2.0f, (float)screenWidth / 2.0f, 
		-(float)screenHeight/2.0f, (float)screenHeight/2.0f, -50.0f, 50.0f);

	//this is what allows the 2d models to scale correctly depending on the screen size
	scaleFactor = (std::min(screenWidth, screenHeight) == screenWidth ? screenWidth / (float)initialWidth : screenHeight / (float)initialHeight);

	//this game over card covers the entire screen, so no need to do code below if this case is true: 
	if (displayGameOverCard) {

		//set color to black so that if screen is too large, it matches the BG of the game over card and the player cannot tell the card is too small to cover the whole screen
		backgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };

		//checks if the correct game over card is already loaded to prevent unneeded reloading of it
		auto checkIfCardNeedsToReload = [&]() {

			GameOverCard::GameOverCardType cardType = gameOverCard->getGameOverCardType();

			if (gameOverType == TIE && cardType == GameOverCard::GameOverCardType::TIE) {

				//game was a tie and the tied card is already loaded
				return false;

			}

			if (winner == player && cardType == GameOverCard::GameOverCardType::WIN) {

				//game was a win and the win card is already loaded
				return false;

			}

			if (winner == O && cardType == GameOverCard::GameOverCardType::LOSS) {

				//game was a loss and the loss card is already loaded
				return false;

			}

			//the incorrect card is currently loaded
			return true;

		};

		if ((gameOverCard == nullptr) || checkIfCardNeedsToReload() /*For optimization: prevents reloading of a card that is already matching the current gameover state*/) {

			//need to reload or load the gameover card
			if (gameOverType == TIE) {

				gameOverCard = new GameOverCard("res/tie.png", GameOverCard::GameOverCardType::TIE); 

			}
			else if (winner == player) {

				gameOverCard = new GameOverCard("res/win.png", GameOverCard::GameOverCardType::WIN);

			}
			else {

				gameOverCard = new GameOverCard("res/lost.png", GameOverCard::GameOverCardType::LOSS);

			}

			gameOverCard->initializeBoardPieceData(); 

		}
	
		gameOverCard->draw(glm::vec3(0.0f, 0.0f, 0.0f), 1024 * scaleFactor, view, proj, 1.0f, false);

		return;

	}

	boardSize = 950.0f * scaleFactor;
	square->DrawSquare(glm::vec3(0.0f, 0.0f, 0.0f), boardSize, glm::vec3(0.0f, 0.0f, 0.0f), view, proj); 

	/*
	
	Draw the grid squares on top of the BG square
	
	*/
	gridOffset = (boardSize / 3) - (10 * scaleFactor); 
	gridSize = gridOffset - (20 * scaleFactor);

	float currentYPos = (boardSize / 3) - (10 * scaleFactor);

	for (int row = 0; row < 3; row++) {

		float currentXPos = -(boardSize / 3) + (10 * scaleFactor); 

		for (int col = 0; col < 3; col++) {

			int index = (row * 3) + col;
			if (gameOver) {

				auto checkIfThisIsWinningPiece = [&]() ->bool {

					if ((gameOverType != ROW) && (gameOverType != COL)) {

						/*
						
						Match may have ended in a tie or is a diagonal win which 
						requires a different type of check that is handled below
						
						*/
						return false; 

					}

					if (theGrid[index] != winner && !checkIfGridConvertingForCharacter(theGrid, index, winner)) {

						/*
						
						The current grid did not match the winning character, so it cannot possibly 
						be colored in as a winning grid
						
						*/
						return false; 

					}

					if (gameOverType == ROW) {

						/*
						
						If the return statement below evaluates to true, then:

							The winning character not only matched the current grid, but it also happens 
							to be that this was a ROW win, and the row this grid is in matches the row 
							the win was detected in
						
						else :

							The winning character not only matched the current grid, but it also happens
							to be that this was a ROW win, but the row this grid is in DOES NOT match the row
							the win was detected in

						*/
						return row == rowOrColWon;

					}

					/*

						If the return statement below evaluates to true, then:

							The winning character not only matched the current grid, but it also happens
							to be that this was a COL win, and the column this grid is in matches the column
							the win was detected in

						else :

							The winning character not only matched the current grid, but it also happens
							to be that this was a column win, but the column this grid is in DOES NOT match the column
							the win was detected in

					*/
					return col == rowOrColWon;

				};

				switch (theGrid[index]) {

					case HOVERING:
						square->DrawSquare(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, glm::vec3(0.0f, 0.0f, 0.0f), view, proj, glm::vec4(0.44f, 0.50f, 0.53f, 1.0f));
						break;
					case X_CONVERTING: 
						XPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, 1.0f, checkIfThisIsWinningPiece(), glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));
						break;																						  
					case X:																							  
						XPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, 1.0f, checkIfThisIsWinningPiece(), glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));
						break;																						   
					case O_CONVERTING: 																				   
						OPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, 1.0f, checkIfThisIsWinningPiece(), glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));
						break;																						   
					case O:																							   
						OPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, 1.0f, checkIfThisIsWinningPiece(), glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));
						break;
					default:
						square->DrawSquare(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, glm::vec3(0.0f, 0.0f, 0.0f), view, proj, glm::vec4(0.44f, 0.50f, 0.53f, 1.0f));
						break;

				}

				//Handle diagonal win drawing: 
				if (gameOverType == TOP_LEFT_TO_BOTTOM_RIGHT_DIAGONAL) {

					if ((index == 0) || (index == 4) || (index == 8)) {

						if (winner == X) {

							XPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, 1.0f, true, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));

						}
						else {

							OPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, 1.0f, true, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));

						}

					}

				}
				else if (gameOverType == TOP_RIGHT_TO_BOTTOM_LEFT_DIAGONAL) {

					if ((index == 2) || (index == 4) || (index == 6)) {

						if (winner == X) {

							XPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, 1.0f, true, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));

						}
						else {

							OPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, 1.0f, true, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));

						}

					}

				}

			}
			else if (resetGame) {

				/*
				
				Do the reset effect 

				-Any grids containing a character are scaled down and spun around and slowly dissolved back to clear grids
				-Grids that were not touched remained intact 

				*/
				float scale = gridSize / 1.15f;
				switch (theGrid[index]) {

					case X_CONVERTING:
						XPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), scale, view, proj, 1.0f - (currentRotationAngle / MAXROTATIONANGLE), false, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f), currentRotationAngle);
						break;																												   
					case X:																													   
						XPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), scale, view, proj, 1.0f - (currentRotationAngle / MAXROTATIONANGLE), false, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f), currentRotationAngle);
						break;																												   
					case O_CONVERTING:																										   
						OPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), scale, view, proj, 1.0f - (currentRotationAngle / MAXROTATIONANGLE), false, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f), currentRotationAngle);
						break;																												   
					case O:																													   
						OPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), scale, view, proj, 1.0f - (currentRotationAngle / MAXROTATIONANGLE), false, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f), currentRotationAngle);
						break;
					default:
						square->DrawSquare(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, glm::vec3(0.0f, 0.0f, 0.0f), view, proj, glm::vec4(0.44f, 0.50f, 0.53f, 1.0f));
						break;

				}

			}
			else {
				
				//a match is currently occuring, draw the grid accordingly
				switch (theGrid[index]) {

					case HOVERING:
						square->DrawSquare(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, glm::vec3(0.0f, 0.0f, 0.0f), view, proj, glm::vec4(0.25f, 0.05f, 0.04f, 1.0f));
						break;
					case X_CONVERTING:
						XPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, obtainLerpFactorForConversionEffect(row, col, X), false, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));
						break;
					case X:
						XPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, 1.0f, false, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f), 0.0f);
						break;
					case O_CONVERTING:
						OPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, obtainLerpFactorForConversionEffect(row, col, O), false, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));
						break;
					case O:
						OPiece->draw(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, view, proj, 1.0f, false, glm::vec4(0.46f, 0.51f, 0.36f, 1.0f));
						break;
					default:
						square->DrawSquare(glm::vec3(currentXPos, currentYPos, 0.0f), gridSize, glm::vec3(0.0f, 0.0f, 0.0f), view, proj, glm::vec4(0.44f, 0.50f, 0.53f, 1.0f));
						break;

				}

			}
			
			currentXPos += gridOffset;

		}

		currentYPos -= gridOffset;

	}

}
