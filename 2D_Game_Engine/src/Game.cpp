#include "Game.h"
#include "TextureManager.h"""
#include "GameObject.h"

#define pr std::cout 
#define el std::endl

GameObject* player;
GameObject* enemy;

SDL_Renderer* Game::renderer = nullptr;		// set to nullptr because we haven't initialised SDL yet

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

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);		// Game Window (boundaries)
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

	player = new GameObject("assets/player.png", 0, 0);
	enemy =  new GameObject("assets/enemy.png", 64, 64);
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

	player->Update();
	enemy->Update();

	pr << cnt << el;
}

void Game::render() {
	SDL_RenderClear(renderer);
	player->Render();
	enemy->Render();
	SDL_RenderPresent(renderer);	
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	pr << "Game cleaned." << el;
}