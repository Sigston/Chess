#include "King.h"

King::King(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'K';
	PieceName = "King";
}

bool King::ValidMove(int DestX, int DestY)
{
	return true;
}
