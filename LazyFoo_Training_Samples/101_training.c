#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#include "my_SDL_Lib.h"

int main() {


	SDL_window**  window = (SDL_window*)malloc(sizeof(SDL_window*));
	window = SDL_init_video();
	SDL_Renderer = SDL_CreateRenderer(*window)



	while
}