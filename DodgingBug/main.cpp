#include "Game.h"
#include "Start.h"

int main()
{
	// Init Game
	bool startGame = true;
	Start start;

	while (start.running())
	{
		start.update();
		start.render();
		startGame = start.getStart();
	}
	if (startGame) {
		Game game;
		// Game loop
		while (game.running()) {
			game.update();
			game.render();
		}
	}

	// End of the application
	return 0;
}