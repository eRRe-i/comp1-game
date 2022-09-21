#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include "my_SDL_Lib.h"

int main () {

	SDL_Window** window = (SDL_Window*) malloc(sizeof(SDL_Window*));
	*window = init_SDL();

	SDL_Surface* surface = loadSurface("05_optimizeSurface/stretch.bmp");
	SDL_Surface* optimizedSurface = loadOptimizedSurface(window, "05_optimizeSurface/stretch.bmp");


	printf("loadSurface format      %u\n", surface->format->format);
	printf("optimizedSurface format %u\n", surface->format->format);

	SDL_FreeSurface(surface);

	loadImage(window, "05_optimizeSurface/stretch.bmp");
	SDL_Delay(1000);

	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;

	SDL_Surface* screenSurface = SDL_GetWindowSurface(*window);

	
	SDL_BlitScaled(optimizedSurface, NULL, screenSurface, &stretchRect);
	SDL_UpdateWindowSurface(*window);

	SDL_Delay(2000);


	SDL_FreeSurface(optimizedSurface);
	close_SDL(window);

	window = NULL;
	surface = NULL;
	optimizedSurface = NULL;

	return 0;
}