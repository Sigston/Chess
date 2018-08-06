#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Piece.h"

class Board
{
public:
	Board();
	std::vector <std::string> GetBoard();
	bool IsEmpty(int XCord, int YCord);
	std::string PieceName(int XCord, int YCord);
	bool IsValidMove(int SourceX, int SourceY, int DestX, int DestY);
	bool IsOwnPiece(int SourceX, int SourceY);
	void MovePiece(int SourceX, int SourceY, int DestX, int DestY);
	std::shared_ptr<Piece> PointerFromCoords(int SourceX, int SourceY);

	bool IsWhitesGo = true;
private:
	std::vector<std::shared_ptr<Piece>> Pieces;
};

