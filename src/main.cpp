#include <stdio.h>

#include "game.h"

int main(int argc, char *argv[])
{
	Game game;

	game.setup();

	while(game.is_running)
	{
		game.process_input();
		game.fix_update();
		game.update();
		game.render();
	}

	game.release_resources();

	return 0;
}
