#pragma once
#include "Piece.h"
class Pawn :
	public Piece
{
public:
	Pawn(int x, int y, bool white);
	bool ValidMove(int DestX, int DestY);
private:
	bool IsFirstGo = true;
};

