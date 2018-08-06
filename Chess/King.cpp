#include "King.h"

King::King(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'k';
	PieceName = "King";
}

bool King::ValidMove(int DestX, int DestY)
{
	int XDiff = abs(DestX - Coords.X);
	int YDiff = abs(DestY - Coords.Y);

	// Limit the move to one square:
	if (XDiff > 1 || YDiff > 1)
	{
		return false;
	}
	// Diagonals:
	if (XDiff == YDiff)
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
