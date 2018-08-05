#include "Queen.h"

Queen::Queen(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'Q';
	PieceName = "Queen";
}

bool Queen::ValidMove(int DestX, int DestY)
{
	return true;
}
