#pragma once
#include "Piece.h"
class Rook :
	public Piece
{
public:
	Rook(int x, int y, bool white);
	bool ValidMove(int DestX, int DestY);
};

