#pragma once
#include <string>

class Piece
{
public:
	Piece(int x, int y, bool white);
	virtual bool ValidMove(int DestX, int DestY);
	int GetX() { return Coords.X; }
	int GetY() { return Coords.Y; }
	bool IsWhite() { return bIsWhite; }
	void Move(int DestX, int DestY);
	char GetChar();
	std::string GetName() { return PieceName; }
protected:
	struct { int X; int Y; } Coords;
	bool bIsWhite;
	char PieceCharacter;
	std::string PieceName;
};
