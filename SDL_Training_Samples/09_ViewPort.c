#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include "my_SDL_Lib.h"

SDL_Texture* loadTexture_fun(SDL_Renderer* renderer, char* pathFile);

int main() {


	SDL_Window** window = (SDL_Window**)malloc(sizeof(SDL_Window*));
	*window = init_SDL_Image();

	SDL_Renderer* renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	SDL_Texture* texture = loadTexture_fun(renderer, "09_ViewPort/viewport.png");

	SDL_Rect topLeftViewport;
    topLeftViewport.x = 0;
    topLeftViewport.y = 0;
    topLeftViewport.w = SCREEN_WIDTH / 2;
    topLeftViewport.h = SCREEN_HEIGHT / 2;

    SDL_Rect topRightViewport;
    topRightViewport.x = SCREEN_WIDTH / 2;
    topRightViewport.y = 0;
    topRightViewport.w = SCREEN_WIDTH / 2;
    topRightViewport.h = SCREEN_HEIGHT / 2;

    SDL_Rect bottomViewport;
    bottomViewport.x = 0;
    bottomViewport.y = SCREEN_HEIGHT / 2;
    bottomViewport.w = SCREEN_WIDTH;
    bottomViewport.h = SCREEN_HEIGHT / 2;


	SDL_Event e;
	bool quit =  false;

	while( !quit )
    {
    //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
           	//User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
          	}
        }
        SDL_RenderClear(renderer);

        SDL_RenderSetViewport( renderer, &topLeftViewport );
       	SDL_RenderCopy(renderer, texture, NULL, NULL);
       	SDL_RenderSetViewport( renderer, &topRightViewport );
       	SDL_RenderCopy(renderer, texture, NULL, NULL);
       	SDL_RenderSetViewport( renderer, &bottomViewport );
       	SDL_RenderCopy(renderer, texture, NULL, NULL);

       	SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    texture = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    IMG_Quit();
    close_SDL(window);
    window = NULL;

}

SDL_Texture* loadTexture_fun(SDL_Renderer* renderer, char* pathFile) {

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(pathFile);

	if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", pathFile, IMG_GetError() );
        return NULL;
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    SDL_FreeSurface(loadedSurface);
    loadedSurface = NULL;

    return newTexture;
}