#include "Queen.h"

Queen::Queen(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'q';
	PieceName = "Queen";
}

bool Queen::ValidMove(int DestX, int DestY)
{
	// Diagonals:
	if (abs(DestX - Coords.X) == abs(DestY - Coords.Y))
	{
		return true;
	}
	// And horizontals:
	if (Coords.X == DestX || Coords.Y == DestY)
	{
		return true;
	}
	return false;
}
