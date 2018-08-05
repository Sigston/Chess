#pragma once
#include "Piece.h"
class Queen :
	public Piece
{
public:
	Queen(int x, int y, bool white);
	bool ValidMove(int DestX, int DestY);
};

