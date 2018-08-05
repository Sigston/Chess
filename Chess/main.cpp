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
	while (game.Menu())
		game.Play();

	return(0);
}
