#include "Pawn.h"
#include <cmath>

Pawn::Pawn(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'p';
	PieceName = "Pawn";
}

bool Pawn::ValidMove(int DestX, int DestY)
{
	// Pawns can only go forward
	if (DestX != Coords.X)
	{
		return false;
	}
	// Can only go forward once, unless it's the first go.
	if (IsFirstGo)
	{
		if (abs(DestY - Coords.Y) == 1 || abs(DestY - Coords.Y) == 2)
		{
			IsFirstGo = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (abs(DestY - Coords.Y) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}
