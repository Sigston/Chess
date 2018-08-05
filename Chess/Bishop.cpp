#include "Bishop.h"

Bishop::Bishop(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'B';
	PieceName = "Bishop";
}

bool Bishop::ValidMove(int DestX, int DestY)
{
	return true;
}
