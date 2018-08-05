#pragma once
#include "Piece.h"
class Knight :
	public Piece
{
public:
	Knight(int x, int y, bool white);
	bool ValidMove(int DestX, int DestY);
};
