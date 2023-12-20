#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texturePath)
{
	SDL_Surface* tempSurface = IMG_Load(texturePath);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}