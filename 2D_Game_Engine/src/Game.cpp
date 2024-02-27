#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

#define pr std::cout 
#define el std::endl


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;		// set to nullptr because we haven't initialised SDL yet
SDL_Event Game::event;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) 
{
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
		isRunning = false;		
	}

	map = new Map();

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/player.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::handleEvents() 
{
	SDL_PollEvent(&event);
	
	switch(event.type) {
		case SDL_QUIT:			// when window's X is clicked > generate an event to stop the game 
			isRunning = false;
			break;
		default: 
			break;
	}
}

void Game::update()
{	
	manager.refresh();
	manager.update();
	
	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		wall.getComponent<ColliderComponent>().collider))
	{
		pr << "Wall hit!" << el;
		player.getComponent<TransformComponent>().scale = 1;
		pr << "Scale: " << player.getComponent<TransformComponent>().scale << el;
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();				// draw first else it doesn't draw it all 
	manager.draw();
	SDL_RenderPresent(renderer);	
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	pr << "Game cleaned." << el;
}