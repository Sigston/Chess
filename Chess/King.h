#pragma once
#include "Piece.h"
class King :
	public Piece
{
public:
	King(int x, int y, bool white);
	bool ValidMove(int DestX, int DestY);
};

