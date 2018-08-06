#include "Bishop.h"
#include <cmath>

Bishop::Bishop(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'b';
	PieceName = "Bishop";
}

bool Bishop::ValidMove(int DestX, int DestY)
{
	if (abs((DestX - Coords.X)) == abs((DestY - Coords.Y)))
	{
		return true;
	}
	return false;
}
