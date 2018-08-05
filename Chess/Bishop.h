#pragma once
#include "Piece.h"
class Bishop :
	public Piece
{
public:
	Bishop(int x, int y, bool white);
	bool ValidMove(int DestX, int DestY);
};

