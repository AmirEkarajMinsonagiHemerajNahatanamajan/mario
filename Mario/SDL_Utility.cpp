#include "SDL_Utility.h"

void drawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
}

SDL_Surface* loadBMP(std::string path) {
	const char* converted_path = path.c_str();
	SDL_Surface* bitmap = SDL_LoadBMP(converted_path);

	return bitmap != nullptr ? bitmap : nullptr;
}

SDL_Surface* loadPNG(std::string path, SDL_Surface* screen) {
	SDL_Surface* optimizedSurface = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != nullptr) {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, 0);
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}


