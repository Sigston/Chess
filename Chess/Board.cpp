#include "Board.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include <memory>
#include <algorithm>

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
	std::shared_ptr<Piece> PiecePtr = PointerFromCoords(XCord, YCord);
	if (PiecePtr == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string Board::PieceName(int XCord, int YCord)
{
	std::string Output = "NO_PIECE";
	std::shared_ptr<Piece> PiecePtr = PointerFromCoords(XCord, YCord);
	if (PiecePtr != nullptr)
	{
		Output = PiecePtr->GetName();
	}
	return(Output);
}

bool Board::IsValidMove(int SourceX, int SourceY, int DestX, int DestY)
{
	// Get a pointer to the piece, check if there was a piece found.
	std::shared_ptr<Piece> PiecePtr = PointerFromCoords(SourceX, SourceY);
	if (PiecePtr == nullptr)
	{
		return false;
	}
	// Is there another friendly piece there?
	std::shared_ptr<Piece> DestPiece = PointerFromCoords(DestX, DestY);
	if (DestPiece != nullptr)
	{
		if ((PiecePtr->IsWhite() && DestPiece->IsWhite()) ||
			(!PiecePtr->IsWhite() && !DestPiece->IsWhite()))
		{
			return false;
		} // Special case of pawn trying to go where there is an enemy piece, and it's trying to move diagonally.
		else 
		{
			if (PiecePtr->GetName() == "Pawn")
			{
				int YOffset = ((PiecePtr->IsWhite()) ? -1 : 1);
				if ((DestY == SourceY + YOffset) &&
					((DestX == SourceX + 1) || (DestX == SourceX - 1)))
				{
					return true;
				}
			}
		}
	}
	// Is there anything in the way?
	if (PiecePtr->GetName() != "Knight")
	{
		int XOffset = ((SourceX == DestX) ? 0 : ((SourceX > DestX) ? -1 : 1));
		int YOffset = ((SourceY == DestY) ? 0 : ((SourceY > DestY) ? -1 : 1));
		int XLook = SourceX + XOffset;
		int YLook = SourceY + YOffset;
		while (!(XLook == DestX && YLook == DestY))
		{
			if (!IsEmpty(XLook, YLook))
			{
				return false;
			}
			XLook += XOffset;
			YLook += YOffset;
		}
	}
	// Given all the above, the last thing is if the piece is moving in its own
	// special way.
	return PiecePtr->ValidMove(DestX, DestY);
}

void Board::ChangeTurn()
{
	bIsWhitesGo = !bIsWhitesGo;
}

bool Board::GameOver()
{
	// If there's only one king, the game is over.
	int counter = 0;
	for (auto it = Pieces.begin(); it < Pieces.end(); ++it)
	{
		if ((*it)->GetName() == "King")
		{
			++counter;
		}
	}
	return ((counter <= 1) ? true : false);
}

bool Board::IsOwnPiece(int SourceX, int SourceY)
{
	std::shared_ptr<Piece> PiecePtr = PointerFromCoords(SourceX, SourceY);
	if (PiecePtr == nullptr)
	{
		return false;
	}

	if ((PiecePtr->IsWhite() && bIsWhitesGo) || (!PiecePtr->IsWhite() && !bIsWhitesGo))
	{
		return true;
	}
	return false;
}

void Board::MovePiece(int SourceX, int SourceY, int DestX, int DestY)
{
	std::shared_ptr<Piece> PiecePtr = PointerFromCoords(SourceX, SourceY);
	if (PiecePtr != nullptr)
	{
		std::shared_ptr<Piece> GetsTaken = PointerFromCoords(DestX, DestY);
		if (GetsTaken != nullptr)
		{
			TakenPieces.push_back(std::shared_ptr<Piece>(GetsTaken));
			Pieces.erase(std::find(Pieces.begin(), Pieces.end(), GetsTaken));
		}
		PiecePtr->Move(DestX, DestY);
	}
}

std::shared_ptr<Piece> Board::PointerFromCoords(int SourceX, int SourceY)
{
	for (auto it = Pieces.begin(); it < Pieces.end(); ++it)
	{
		if ((*it)->GetX() == SourceX && (*it)->GetY() == SourceY)
		{
			return *it;
		}
	}
	return nullptr;
}

std::vector<char> Board::ListTakenPieces()
{
	std::vector<char> Output;
	for (auto it = TakenPieces.begin(); it < TakenPieces.end(); ++it)
	{
		Output.push_back((*it)->GetChar());
	}
	return(Output);
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
	for (unsigned int x = 0; x < Output.size(); ++x)
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