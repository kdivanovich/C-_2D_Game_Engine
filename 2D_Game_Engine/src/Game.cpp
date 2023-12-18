#include "Game.h"
#include "TextureManager.h"""

#define pr std::cout 
#define el std::endl

SDL_Texture* playerTex;
SDL_Rect srcR, destR; 

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0; 
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		pr << "Subsystems initialized." << el;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)	{
			pr << "Window created." << el;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			pr << "Renderer created." << el;
		}

		isRunning = true;
	}
	else {
		isRunning = false;		// was removed?
	}

	playerTex = TextureManager::LoadTexture("assets/player.png", renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch(event.type) {
		case SDL_QUIT:				// when window's X is clicked > generate an event to stop the game 
			isRunning = false;
			break;
		default: 
			break;
	}
}

void Game::update()
{
	cnt++;

	// Set destination rectangle size:
	destR.h = 64;
	destR.w = 64; 

	destR.x = cnt;	// Move to the right 1 pixel at a time

	pr << cnt << el;
}

void Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, playerTex, NULL, &destR);	// 1st rect = use entire image, destR = draw the render frame
	SDL_RenderPresent(renderer);	
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	pr << "Game cleaned." << el;
}