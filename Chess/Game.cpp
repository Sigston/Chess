#include "Game.h"
#include <string>
#include <iostream>

Game::Game(Drawer * drawerPointer) :
	Draw(drawerPointer), GameBoard()
{
}

void Game::Play()
{
	// Draw board, request move, change game state, 
	// check if anyone has won or if there is a stalemate, repeat.
	bool IsPlaying = true;
	while (IsPlaying)
	{
		// Get the coordinates and check if this is a valid move.
		unsigned int SourceX = 8;
		unsigned int SourceY = 8;
		unsigned int DestX = 8;
		unsigned int DestY = 8;
		bool CorrectMove = false;
		while (!CorrectMove)
		{
			DrawBoard(GameBoard.GetBoard());
			Draw->Text("Piece X Coordinate.");
			while (SourceX > 7)
			{
				Draw->UserPrompt();
				ValidInputUInt(SourceX, Draw->GetUserPrompt());
			}
			Draw->Text("Piece Y Coordinate.");
			while (SourceY > 7)
			{
				Draw->UserPrompt();
				ValidInputUInt(SourceY, Draw->GetUserPrompt());
			}
			Draw->Text("Destination X Coordinate.");
			while (DestX > 7)
			{
				Draw->UserPrompt();
				ValidInputUInt(DestX, Draw->GetUserPrompt());
			}
			Draw->Text("Destination Y Coordinate.");
			while (DestY > 7)
			{
				Draw->UserPrompt();
				ValidInputUInt(DestY, Draw->GetUserPrompt());
			}
			std::string Error;
			if (ValidateMove(SourceX, SourceY, DestX, DestY, Error))
			{
				CorrectMove = true;
			}
			else
			{
				Draw->BlankLine();
				Draw->Text(Error);
				SourceX = SourceY = DestX = DestY = 8;
				CorrectMove = false;
				Wait();
			}
		}
		GameBoard.MovePiece(SourceX, SourceY, DestX, DestY);
		GameBoard.IsWhitesGo = !GameBoard.IsWhitesGo;
		Draw->BlankLine();
		Draw->Seperator();
	}
}

bool Game::ValidateMove(int SourceX, int SourceY, int DestX, int DestY, std::string &Error)
{
	if (GameBoard.IsEmpty(SourceX, SourceY))
	{
		Error = "Please select a piece.";
		return false;
	}
	if (!GameBoard.IsOwnPiece(SourceX, SourceY))
	{
		Error = "Please select your own piece (white is lower case, black is upper case).";
		return false;
	}
	if (!GameBoard.IsValidMove(SourceX, SourceY, DestX, DestY))
	{
		Error = "Please choose a valid move.";
		return false;
	}
	// Is there anything in the way?
	std::shared_ptr<Piece> ChosenPiece = GameBoard.PointerFromCoords(SourceX, SourceY);
	if (ChosenPiece->GetName() != "Knight")
	{
		// There will always be a straight line, diagonal, horizontal or vertical, between where the piece
		// is and where it wants to be. I need to check every point on that line to see if it is empty. If
		// any of them aren't, we return false. If they are all empty, we can leave the loop.
		int XVal = 0;
		int YVal = 0;
		if (SourceX == DestX)
		{
			XVal = 0;
		}
		else if (SourceX > DestX)
		{
			XVal = -1;
		}
		else if (DestX > SourceX)
		{
			XVal = 1;
		}
		if (SourceY == DestY)
		{
			YVal = 0;
		}
		else if (SourceY > DestY)
		{
			YVal = -1;
		}
		else if (DestY > SourceY)
		{
			YVal = 1;
		}
		int XLook = SourceX + XVal;
		int YLook = SourceY + YVal;
		while (!(XLook == DestX && YLook == DestY))
		{
			if (!GameBoard.IsEmpty(XLook, YLook))
			{
				Error = "You cannot move through another piece!";
				return false;
			}
			XLook += XVal;
			YLook += YVal;
		}
	}
	return true;
}

void Game::DrawBoard(std::vector<std::string> Board)
{
	Draw->BlankLine();
	Draw->Seperator();
	Draw->BlankLine();
	for (int x = 0; x < Board.size(); ++x)
	{
		Draw->Text(Board[x]);
	}
	Draw->BlankLine();
	if (GameBoard.IsWhitesGo)
	{
		Draw->Text("It is white's go!");
	}
	else
	{
		Draw->Text("It is black's go!");
	}
	Draw->BlankLine();
	std::vector<char> TakenPieces = GameBoard.ListTakenPieces();
	std::string TakenPiecesString = "Taken Pieces: ";
	for (auto it = TakenPieces.begin(); it < TakenPieces.end(); ++it)
	{
		TakenPiecesString.append(std::string(1, *it) + " ");
	}
	Draw->Text(TakenPiecesString);
	Draw->BlankLine();
}

void Game::Introduction()
{
	Draw->Seperator();
	Draw->BlankLine();
	Draw->CentralLine("CHESS");
	Draw->BlankLine();
	Draw->Seperator();
	Draw->BlankLine();
	Draw->CentralLine("The Ancient Game of Chess");
	Draw->BlankLine();
	Draw->BlankLine();
	Draw->CentralLine("Implemented By Alex Sigston");
	Draw->BlankLine();
	Draw->Seperator();
}

bool Game::Menu()
{
	int Decision = 0;
	bool PlayGame;

	while (true)
	{
		Draw->BlankLine();
		Draw->Text("Would you like to (1) play a game, (2) see the rules, (3) quit the game?");

		// Get a valid decision
		while (Decision < 1 || Decision > 3)
		{
			Draw->UserPrompt();
			ValidInputInt(Decision, Draw->GetUserPrompt());
		}

		// Do the right thing
		switch (Decision)
		{
		case 3:
			PlayGame = false;
			break;
		case 2:
			PrintRules();
			break;
		case 1:
			PlayGame = true;
			break;
		}
		if (Decision == 1 || Decision == 3)
			break;
		Decision = 0;
	}
	return(PlayGame);
}

void Game::PrintRules()
{
	Draw->Seperator();
	Draw->BlankLine();
	Draw->Text("This program is an implementation of the ancient game of chess. "
		"Two players battle against each other in the ultimate game of wits and strategy. "
		"Do you have what it takes to win?");
	Draw->BlankLine();
	// Basic rules:
	Draw->Text("In chess, moving on top of another piece removes it from the board. You lose "
		"the game if, on your next turn, there is nothing you can do to stop your King being removed from "
		"the board. This is known as 'checkmate'; the threat against your King is called 'check'. "
		"Knights move in an 'L' shape and are the only pieces which can jump over other pieces. Bishops "
		"move diagonally in any direction as far as they wish. Rooks are similar, but move only in straight "
		"lines. The Queen can both in straight lines and diagonally. The King moves the same as the Queen, but "
		"only one square at a time. The pawns move only one square forwards, apart from on their first move "
		"when they can move twice. Pawns can also move one space diagonally - but only when moving on to "
		"a square occupied by an opponent's piece.");
	Draw->BlankLine();
	Draw->Text("There are two special rules in Chess. The first is castling. If you have not moved "
		"your King or rook this game, and doing so would not move your King through check or into check, "
		"you may swap around your King and rook either on the side of the King (moving the King two squares "
		"in the rook's direction and placing the rook on the other side) or on the side of the Queen (moving "
		"the King three squares in the rook's direction and placing the rook on the other side). Secondly, "
		"en passant. En passant is a special pawn capture that can only occur immediately after a pawn "
		"moves two squares forward from its starting square and an enemy pawn that could have captured it "
		"had it only moved forward only one square.");
	// How to operate the pieces in this program:
	Draw->BlankLine();
	Draw->CentralLine("HAVE FUN!!!");
	Draw->BlankLine();
	Draw->Seperator();
}

void Game::ValidInputChar(char &OutputChar, std::string ErrorMessage)
{
	std::cin >> OutputChar;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << ErrorMessage;
		std::cin >> OutputChar;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::ValidInputInt(int &OutputInt, std::string ErrorMessage)
{
	std::cin >> OutputInt;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << ErrorMessage;
		std::cin >> OutputInt;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::ValidInputUInt(unsigned int &OutputInt, std::string ErrorMessage)
{
	std::cin >> OutputInt;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << ErrorMessage;
		std::cin >> OutputInt;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::ValidInputStr(std::string &OutputStr, std::string ErrorMessage)
{
	std::getline(std::cin, OutputStr);
}

void Game::Wait()
{
	Draw->UserPrompt();
	std::cin.ignore();
}