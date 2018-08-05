#include "Board.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include <memory>

Board::Board()
{
	// Set up the board with pointers to new pieces
	Pieces.push_back(std::shared_ptr<Piece>(new Knight(1, 0, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Knight(6, 0, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Knight(1, 7, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Knight(6, 7, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Rook(0, 0, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Rook(7, 0, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Rook(0, 7, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Rook(7, 7, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Bishop(2, 0, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Bishop(5, 0, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Bishop(2, 7, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Bishop(5, 7, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new King(4, 0, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new King(4, 7, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Queen(3, 0, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Queen(3, 7, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(0, 1, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(1, 1, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(2, 1, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(3, 1, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(4, 1, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(5, 1, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(6, 1, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(7, 1, false)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(0, 6, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(1, 6, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(2, 6, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(3, 6, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(4, 6, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(5, 6, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(6, 6, true)));
	Pieces.push_back(std::shared_ptr<Piece>(new Pawn(7, 6, true)));
}

bool Board::IsEmpty(int XCord, int YCord)
{
	for (auto it = Pieces.begin(); it < Pieces.end(); ++it)
	{
		if ((*it)->GetX() == XCord && (*it)->GetY() == YCord)
		{
			return false;
		}
	}
	return true;
}

std::string Board::PieceName(int XCord, int YCord)
{
	std::string Output = "NO_PIECE";
	for (auto it = Pieces.begin(); it < Pieces.end(); ++it)
	{
		if ((*it)->GetX() == XCord && (*it)->GetY() == YCord)
		{
			Output = (*it)->GetName();
		}
	}
	return(Output);
}

bool Board::IsValidMove(int SourceX, int SourceY, int DestX, int DestY)
{
	// Can the piece move in this kind of way?
	for (auto it = Pieces.begin(); it < Pieces.end(); ++it)
	{
		if ((*it)->GetX() == SourceX && (*it)->GetY() == SourceY)
		{
			return (*it)->ValidMove(DestX, DestY);
		}
	}

	// If it isn't a knight, are there pieces in the way?

	return false;
}

void Board::MovePiece(int SourceX, int SourceY, int DestX, int DestY)
{
	if (IsValidMove(SourceX, SourceY, DestX, DestY))
	{
		for (auto it = Pieces.begin(); it < Pieces.end(); ++it)
		{
			if ((*it)->GetX() == SourceX && (*it)->GetY() == SourceY)
			{
				(*it)->Move(DestX, DestY);
			}
		}
	}
	else
		return;
}

std::vector<std::string> Board::GetBoard()
{
	// Initial board.
	std::vector <std::string> Output = {
		"--------",
		"--------",
		"--------",
		"--------",
		"--------",
		"--------",
		"--------",
		"--------"
	};

	// Put in the pieces.
	for (auto it = Pieces.begin(); it < Pieces.end(); ++it)
	{
		int XCord = (*it)->GetX();
		int YCord = (*it)->GetY();
		Output[YCord][XCord] = (*it)->GetChar();
	}
	
	// Separate the squares out to look nice.
	for (int x = 0; x < Output.size(); ++x)
	{
		Output[x] = std::string(std::to_string(x) + "|" + std::string(1, Output[x][0]) + "|" + 
			std::string(1, Output[x][1]) + "|" + std::string(1, Output[x][2]) + "|" + 
			std::string(1, Output[x][3]) + "|" + std::string(1, Output[x][4]) + "|" + 
			std::string(1, Output[x][5]) + "|" + std::string(1, Output[x][6]) + "|" + 
			std::string(1, Output[x][7]) + "|");
	}

	// Add the top and bottom of the board.
	Output.insert(Output.begin(), " -----------------");
	Output.insert(Output.begin(), "  0 1 2 3 4 5 6 7");
	Output.push_back(" -----------------");
	return(Output);
}