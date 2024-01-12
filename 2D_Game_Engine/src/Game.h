#pragma once

#ifndef Game_hpp
#define Game_hpp
#define SDL_MAIN_HANDLED	//uncomment
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

#endif 

class Game
{
public: 
	Game();		//constor
	~Game();	// destructor

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);	// init method to start the game 

	void handleEvents();
	void update();
	void render();
	void clean();							// memory management
	bool running() { return isRunning; }	// inline func; let the main func know the game's still running

	static SDL_Renderer* renderer;			// make it globally available as passing it as a private var creates copies
	static SDL_Event event;

private:
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
};

