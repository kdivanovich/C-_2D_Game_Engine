#pragma once

#include "Game.h"

class GameObject
{
public:
	// Constructor/destructor
	GameObject(const char* textureSheetPath, SDL_Renderer* ren);
	~GameObject();

	void Update();
	void Render();

private:
	int xPos;
	int yPos; 

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;


};

