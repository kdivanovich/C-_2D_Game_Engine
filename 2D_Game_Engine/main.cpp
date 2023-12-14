#include <iostream>
#include "Game.h"
#define pr std::cout 


Game* game = nullptr;

int main(int argc, int* argv[]) {
	const int FPS = 60;	
	const int frameDelay = 1000 / FPS;		// max itme between frames

	Uint32 frameStart; 
	int frameTime;

	game = new Game();
	game->init("Stan Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);


	while (game->running()) {
		frameStart = SDL_GetTicks();		// how many ms it's been since we initialised SDL

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;	// how long in ms it's taken between handling our events, updating the obj, and rendering it

		if (frameDelay > frameTime) {				// check if we need to delay running the next frame
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->clean();

	return 0;
}