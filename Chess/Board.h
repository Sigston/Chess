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
	void MovePiece(int SourceX, int SourceY, int DestX, int DestY);
private:
	std::vector<std::shared_ptr<Piece>> Pieces;
};

