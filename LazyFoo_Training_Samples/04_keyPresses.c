#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include "my_SDL_Lib.h"

bool load_KeySurfaces(SDL_Surface** keySurfaces);

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

int main (){


	SDL_Window** window = (SDL_Window*)malloc(sizeof(SDL_Window*));
	*window = init_SDL();

	SDL_Surface** keySurfaces = (SDL_Surface*)malloc(sizeof(SDL_Surface*)*KEY_PRESS_SURFACE_TOTAL);


	load_KeySurfaces(keySurfaces);

	keyEventHandler(window, keySurfaces);


	for(int i=0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
		SDL_FreeSurface(keySurfaces[i]);
	}

	close_SDL(window);

	window = NULL;
	keySurfaces = NULL;

	return 0;
	}



void keyEventHandler(SDL_Window** pWindow, SDL_Surface** keySurfaces) {


	SDL_Event e;
	bool quit = false;

	SDL_Surface* windowSurface = SDL_GetWindowSurface( *pWindow );

	SDL_Surface* currentSurface = keySurfaces[KEY_PRESS_SURFACE_DEFAULT];

	while(!quit) {

		while(SDL_PollEvent( &e ) != 0) {

			if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {

				switch( e.key.keysym.sym ) {

					case SDLK_UP:
					currentSurface = keySurfaces[KEY_PRESS_SURFACE_UP];
					break;

					case SDLK_DOWN:
					currentSurface = keySurfaces[KEY_PRESS_SURFACE_DOWN];
					break;

					case SDLK_LEFT:
					currentSurface = keySurfaces[KEY_PRESS_SURFACE_LEFT];
					break;

					case SDLK_RIGHT:
					currentSurface = keySurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;
				}
			}
		}

		SDL_BlitSurface(currentSurface, NULL, windowSurface, NULL);
		SDL_UpdateWindowSurface(*pWindow);
	}

	currentSurface = NULL;
	windowSurface = NULL;
}


bool load_KeySurfaces(SDL_Surface** keySurfaces) {


	for(int i=0; i<KEY_PRESS_SURFACE_TOTAL; i++) {

		keySurfaces[i] = NULL;
	}

	keySurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("04_key_presses/press.bmp");
	if( keySurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        return false;
    }

	keySurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("04_key_presses/up.bmp");
	if( keySurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        return false;
    }

	keySurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("04_key_presses/down.bmp");
	if( keySurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        return false;
    }

	keySurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("04_key_presses/left.bmp");
	if( keySurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        return false;
    }
	keySurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("04_key_presses/right.bmp");
	if( keySurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        return false;
    }

    return true;

}