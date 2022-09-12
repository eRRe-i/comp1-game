#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include "my_SDL_Lib.h"

int main() {

	SDL_Window** window = (SDL_Window*) malloc(sizeof(SDL_Window*));
	*window = init_SDL_Image();


	loadImage_IMG(window, "06_PNG_load/loaded.png");
	SDL_Delay( 2000 );

	close_SDL(window);

	IMG_Quit();

	window = NULL;

	return 0;
}
