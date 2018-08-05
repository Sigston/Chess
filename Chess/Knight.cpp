#include "Knight.h"
#include <vector>

Knight::Knight(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'N';
	PieceName = "Knight";
}

bool Knight::ValidMove(int DestX, int DestY)
{
	// On an infinite board, there are always 8 possible squares for the knight to move to.
	if (Coords.X - 1 == DestX && Coords.Y - 2 == DestY)
	{
		return true;
	}
	else if (Coords.X - 2 == DestX && Coords.Y - 1 == DestY)
	{
		return true;
	}
	else if (Coords.X - 2 == DestX && Coords.Y + 1 == DestY)
	{
		return true;
	}
	else if (Coords.X - 1 == DestX && Coords.Y + 2 == DestY)
	{
		return true;
	}
	else if (Coords.X + 1 == DestX && Coords.Y - 2 == DestY)
	{
		return true;
	}
	else if (Coords.X + 2 == DestX && Coords.Y - 1 == DestY)
	{
		return true;
	}
	else if (Coords.X + 2 == DestX && Coords.Y + 1 == DestY)
	{
		return true;
	}
	else if (Coords.X + 1 == DestX && Coords.Y + 2 == DestY)
	{
		return true;
	}

	return false;
}
