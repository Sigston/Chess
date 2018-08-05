#include "Rook.h"

Rook::Rook(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'R';
	PieceName = "Rook";
}

bool Rook::ValidMove(int DestX, int DestY)
{
	return true;
}
