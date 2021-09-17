/*

Creator: Diego Avena
Last Updated: 9/17/21

*/

#ifndef GAME_OVER_CARD
#define GAME_OVER_CARD

#include "../boardPieceRenderer/BoardPiece.h"

/*

Contains all the functionality needed to render 
a card that tells the player how the current match 
ended: a Loss, a Win, or a Tie

*/
class GameOverCard: public BoardPiece {

public:
	enum GameOverCardType {

		WIN,
		LOSS,
		TIE

	};

	GameOverCard(const char* textureImagePath, GameOverCardType type); 

	inline GameOverCardType getGameOverCardType() const {

		return cardType;

	}

private:
	GameOverCardType cardType;

};

#endif