#include "Bishop.h"

Bishop::Bishop(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'B';
	PieceName = "Bishop";
}

bool Bishop::ValidMove(int DestX, int DestY)
{
	// Two diagonals.
	if ((DestX - Coords.X) == (DestY - Coords.Y))
	{
		return true;
	}
	else if (((DestX - Coords.X) + (DestY - Coords.Y)) == 0)
	{
		return true;
	}
	else if (((DestX - Coords.X) - (DestY - Coords.Y)) == 0)
	{
		return true;
	}
	return false;
}
