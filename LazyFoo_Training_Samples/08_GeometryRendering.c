#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include "my_SDL_Lib.h"

int main() {

	SDL_Window** window = (SDL_Window*)malloc(sizeof(SDL_Window*));
	*window = init_SDL_Image();

	SDL_Renderer** renderer =  (SDL_Renderer*)malloc(sizeof(SDL_Renderer*));
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

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
		SDL_SetRenderDrawColor( *renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(*renderer);

		SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		SDL_SetRenderDrawColor( *renderer, 0xFF, 0x00, 0x00, 0xFF );
		SDL_RenderFillRect( *renderer, &fillRect );

		SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
        SDL_SetRenderDrawColor( *renderer, 0x00, 0xFF, 0x00, 0xFF );        
        SDL_RenderDrawRect( *renderer, &outlineRect );

        SDL_SetRenderDrawColor( *renderer, 0x00, 0x00, 0xFF, 0xFF );        
        SDL_RenderDrawLine( *renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

        SDL_SetRenderDrawColor( *renderer, 0xFF, 0xFF, 0x00, 0xFF );
            for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
            {
                SDL_RenderDrawPoint( *renderer, SCREEN_WIDTH / 2, i );
            }
        SDL_RenderPresent( *renderer );
	}

	close_SDL(window);
	IMG_Quit();


	return 0;
}