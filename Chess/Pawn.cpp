#include "Pawn.h"

Pawn::Pawn(int x, int y, bool white) : Piece(x, y, white)
{
	PieceCharacter = 'P';
	PieceName = "Pawn";
}

bool Pawn::ValidMove(int DestX, int DestY)
{
	return true;
}
