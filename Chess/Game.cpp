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
	bool WhitesGo = true;
	Draw->BlankLine();
	Draw->Seperator();
	Draw->BlankLine();
	Draw->Text("White goes first.");
	Draw->BlankLine();
	Draw->Seperator();
	while (IsPlaying)
	{
		Draw->BlankLine();
		std::vector<std::string> Board = GameBoard.GetBoard();
		for (int x = 0; x < Board.size(); ++x)
		{
			Draw->Text(Board[x]);
		}
		Draw->BlankLine();
		if (WhitesGo)
		{
			Draw->Text("It is white's go!");
		}
		else
		{
			Draw->Text("It is black's go!");
		}
		Draw->BlankLine();

		// Get the coordinate of the piece.
		Draw->Text("Enter the coordinates of the piece you would like to move.");
		unsigned int SourceX = 8;
		unsigned int SourceY = 8;
		while(true)
		{
			Draw->Text("X Coordinate.");
			while (SourceX > 7)
			{
				Draw->UserPrompt();
				ValidInputUInt(SourceX, Draw->GetUserPrompt());
			}
			Draw->Text("Y Coordinate.");
			while (SourceY > 7)
			{
				Draw->UserPrompt();
				ValidInputUInt(SourceY, Draw->GetUserPrompt());
			}
			if (GameBoard.IsEmpty(SourceX, SourceY))
			{
				Draw->BlankLine();
				Draw->Text("Please select a piece.");
				Draw->BlankLine();
				SourceX = 8;
				SourceY = 8;
			}
			else
				break;
		}

		Draw->BlankLine();
		Draw->Text("To where would you like to move the " + GameBoard.PieceName(SourceX, SourceY) 
			+ " at " + std::to_string(SourceX) + ", " + std::to_string(SourceY) + "?");
		unsigned int DestX = 8;
		unsigned int DestY = 8;
		while (true)
		{
			Draw->Text("X Coordinate.");
			while (DestX > 7)
			{
				Draw->UserPrompt();
				ValidInputUInt(DestX, Draw->GetUserPrompt());
			}
			Draw->Text("Y Coordinate.");
			while (DestY > 7)
			{
				Draw->UserPrompt();
				ValidInputUInt(DestY, Draw->GetUserPrompt());
			}

			if (!GameBoard.IsValidMove(SourceX, SourceY, DestX, DestY))
			{
				Draw->BlankLine();
				Draw->Text("Please choose a valid move.");
				Draw->BlankLine();
				DestX = 8;
				DestY = 8;
			}
			else
			{
				GameBoard.MovePiece(SourceX, SourceY, DestX, DestY);
				break;
			}

		}

		WhitesGo = !WhitesGo;
		Draw->BlankLine();
		Draw->Seperator();
	}
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
