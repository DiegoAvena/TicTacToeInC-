#ifndef GAME_OVER_CARD
#define GAME_OVER_CARD

#include "../boardPieceRenderer/BoardPiece.h"

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