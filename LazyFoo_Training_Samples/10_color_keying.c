#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

typedef struct image {

	int height;
	int width;
	SDL_Texture* texture; 
	char pathName[50];

} Image;

Image* init_Texture(SDL_Renderer* renderer, char *pathName, int width, int height);
void renderTexture(SDL_Renderer* renderer, Image *image, int x, int y);

#include "my_SDL_Lib.h"

int main () {

	SDL_Window** window = (SDL_Window**)malloc(sizeof(SDL_Window*));
	*window = init_SDL_Image(); 

	SDL_Renderer* renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

	Image *foo = (Image*)malloc(sizeof(Image));
	Image *background = (Image*)malloc(sizeof(Image));

	background->texture = loadTexture(renderer, "10_color_keying/background.png");

	foo = init_Texture(renderer, "10_color_keying/foo.png", 64, 128);
	background = init_Texture(renderer, "10_color_keying/background.png", 640, 480);

	SDL_Event e;
	bool quit = false;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	while( !quit ) {
                //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ) {
                    //User requests quit
           	if( e.type == SDL_QUIT ) {

                    quit = true;
                }
			}

		SDL_RenderClear( renderer );

		renderTexture(renderer, background, 0, 0);
		renderTexture(renderer, foo, 240, 190);
		
		
		//SDL_RenderCopy(renderer, background->texture, NULL, NULL);


		SDL_RenderPresent(renderer);


	}

	IMG_Quit();
	SDL_Quit();

	return 0;

}

Image* init_Texture(SDL_Renderer* renderer, char *pathFile, int width, int height) {

	SDL_Surface* loadedSurface = NULL;

	Image *image = (Image*)malloc(sizeof(Image));

	loadedSurface = loadSurface_IMG(pathFile);

	if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", pathFile, IMG_GetError() );
    }
    else
    {
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
	}

	strcpy(image->pathName, pathFile);
	image->height = height;
	image->width = width;
	
	image->texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	SDL_FreeSurface(loadedSurface);
	loadedSurface = NULL;

	return image;
}

void renderTexture(SDL_Renderer* renderer, Image* image, int x, int y) {

	SDL_Rect renderQuad = { x, y, image->width, image->height };
	SDL_RenderCopy(renderer, image->texture, NULL, &renderQuad);
}