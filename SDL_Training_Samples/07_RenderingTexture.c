#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include "my_SDL_Lib.h"

SDL_Texture* loadTexture_fun(SDL_Renderer** pRenderer, char* pathFile);

int main() {

	SDL_Window** window = (SDL_Window**) malloc(sizeof(SDL_Window*));
	*window = init_SDL_Image();

	SDL_Renderer** renderer = (SDL_Renderer*) malloc(sizeof(SDL_Renderer*));
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor( *renderer, 0xFF, 0xFF, 0xFF, 0xFF );


	SDL_Texture* texture = loadTexture_fun(renderer, "07_RenderingTexture/texture.png");

	SDL_Event e;
	bool quit = false;

	while(!quit) {

		while(SDL_PollEvent(&e) != 0) {

			if(e.type == SDL_QUIT) {

				quit = true;
			}
		
		}

		SDL_RenderClear(*renderer);
		SDL_RenderCopy(*renderer, texture, NULL, NULL);
		SDL_RenderPresent( *renderer );
	}

	SDL_DestroyTexture(texture);
	texture = NULL;

	SDL_DestroyRenderer(*renderer);
	*renderer = NULL;
	renderer = NULL;

	SDL_DestroyWindow(*window);
	*window = NULL;
	window = NULL;

	return 0;
}

SDL_Texture* loadTexture_fun(SDL_Renderer** pRenderer, char* pathFile) {

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(pathFile);

	if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", pathFile, IMG_GetError() );
        return NULL;
    }

    newTexture = SDL_CreateTextureFromSurface(*pRenderer, loadedSurface);

    SDL_FreeSurface(loadedSurface);
    loadedSurface = NULL;

    return newTexture;
}

