#include "Piece.h"

Piece::Piece(int x, int y, bool white) :
	IsWhite(white)
{
	Coords.X = x;
	Coords.Y = y;
}

bool Piece::ValidMove(int DestX, int DestY)
{
	return false;
}

void Piece::Move(int DestX, int DestY)
{
	Coords.X = DestX;
	Coords.Y = DestY;
}
