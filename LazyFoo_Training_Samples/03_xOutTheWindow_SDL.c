#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include "my_SDL_Lib.h"

int main (){


	SDL_Window** window = (SDL_Window*) malloc(sizeof(SDL_Window*));
	*window = init_SDL();

	//fprintf(stderr,"Surface gotten!\n");

	bool quit = false;

	SDL_Event e;

	//While application is running
	while( !quit ){
	//Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ){
            //User requests quit
            if( e.type == SDL_QUIT ){
                quit = true;
            }
        }
        loadImage(window, "03_xOut_window/x_out.bmp");
    }

	close_SDL(window);


	return 0;

}

