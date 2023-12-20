#pragma once

#include "Game.h"

class GameObject
{
public:
	// Constructor/destructor
	GameObject(const char* textureSheetPath, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xPos;
	int yPos; 

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};

