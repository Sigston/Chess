#pragma once
#include "Drawer.h"
#include "Board.h"
#include <string>

class Game
{
public:
	Game(Drawer * drawerPointer);
	void Introduction();
	bool Menu();
	void Play();
private:
	Drawer * Draw;
	Board GameBoard;

	void PrintRules();
	void ValidInputChar(char &OutputChar, std::string ErrorMessage);
	void ValidInputInt(int &OutputInt, std::string ErrorMessage);
	void ValidInputUInt(unsigned int &OutputInt, std::string ErrorMessage);
	void ValidInputStr(std::string &OutputStr, std::string ErrorMessage);
	bool ValidateMove(int SourceX, int SourceY, int DestX, int DestY, std::string &Error);
	void DrawBoard(std::vector<std::string> Board);
	void Wait();
};

