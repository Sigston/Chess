// TODO:
//	Make the rules a bit clearer.

#include <string>
#include "Drawer.h"
#include "Board.h"
#include "Game.h"

int main()
{
	Drawer drawer(70, 3, '|', "|   : ");
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
