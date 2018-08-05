// TODO:
//	Make the rules a bit clearer.

#include <string>
#include "Drawer.h"
#include "Board.h"
#include "Game.h"

const unsigned short SCREEN_SPACE = 70;
const unsigned short PADDING = 3;
const char SCREEN_CHARACTER = '|';
const std::string USER_PROMPT = "|   : ";

int main()
{
	Drawer drawer(SCREEN_SPACE, PADDING, SCREEN_CHARACTER, USER_PROMPT);
	Game game(&drawer);

	game.Introduction();
	bool Playing = game.Menu();
	while (Playing)
	{
		game.Play();
		Playing = game.Menu();
	}

	return(0);
}
