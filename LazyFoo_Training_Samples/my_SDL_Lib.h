#ifndef _MY_SDL_LIB

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

SDL_Window* init_SDL();
SDL_Window* init_SDL_Image();
void close_SDL_Surface(SDL_Window** window, SDL_Surface** surface);
void close_SDL(SDL_Window** window);
SDL_Surface* loadOptimizedSurface(SDL_Window** window, char* pathFile);
bool loadImage(SDL_Window** window, char* pathFile);
SDL_Surface* loadSurface_IMG(char* pathFile);
SDL_Texture* loadTexture(SDL_Renderer* renderer, char* pathFile);


SDL_Window* init_SDL() {

	SDL_Window* window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL could not initialize! ERROR: %s\n", SDL_GetError());
		return NULL;
	}
	else {
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(window == NULL) {
			printf("Could not create window! ERROR: %s\n", SDL_GetError());
			return NULL;
		}
	}
	//fprintf(stderr, "Window Created!\n");
	return window;
}

void close_SDL_Surface(SDL_Window** window, SDL_Surface** surface) {

	SDL_FreeSurface(*surface);
	*surface = NULL;

	SDL_DestroyWindow(*window);
	*window = NULL;

	SDL_Quit();
	fprintf(stderr,"SDL Closed\n");
	return;
}

void close_SDL(SDL_Window** window) {

	SDL_DestroyWindow(*window);
	*window = NULL;

	SDL_Quit();
	//fprintf(stderr,"SDL Closed\n");
	return;
}

SDL_Surface* loadOptimizedSurface(SDL_Window** window, char* pathFile) {

	SDL_Surface* loadedSurface = NULL;
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* screenSurface = SDL_GetWindowSurface(*window);

	loadedSurface = SDL_LoadBMP(pathFile);

	if (loadedSurface == NULL){
		printf("Unable to load file! Error: %s\n", SDL_GetError());
		return NULL;
	}
	else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
		if (optimizedSurface == NULL) {
			printf("Unable to load optimized Surface! Error: %s\n", SDL_GetError());
		}
	}

	SDL_FreeSurface(loadedSurface);
	loadedSurface = NULL;
	screenSurface = NULL;

	return optimizedSurface;
}

bool loadImage(SDL_Window** window, char* pathFile) {

	SDL_Surface* windowSurface = SDL_GetWindowSurface(*window);

	SDL_Surface* pathSurface = loadOptimizedSurface(window, pathFile);

	SDL_BlitSurface(pathSurface, NULL, windowSurface, NULL);
	SDL_UpdateWindowSurface(*window);

	SDL_FreeSurface(pathSurface);

	pathSurface = NULL;
	windowSurface = NULL;

	return true;
}

SDL_Surface* loadSurface (char* pathFile) {

	SDL_Surface* pathSurface = NULL;

	pathSurface = SDL_LoadBMP(pathFile);
	if(pathSurface == NULL) {
		printf("Unable to load file! Error: %s\n", SDL_GetError());
		return NULL;
	}

	return pathSurface;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~AULA 06
SDL_Window* init_SDL_Image() {

	SDL_Window* window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL could not initialize! ERROR: %s\n", SDL_GetError());
		return NULL;
	}
	else {
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(window == NULL) {
			printf("Could not create window! ERROR: %s\n", SDL_GetError());
			return NULL;
		}
		else {

			int imgFlags = IMG_INIT_PNG;
			if ( !(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize: Error:%s\n", IMG_GetError());



			}
		}
	}
	//fprintf(stderr, "Window Created!\n");
	return window;
}


void loadImage_IMG(SDL_Window** pWindow, char* pathFile) {

	SDL_Surface* surface = loadSurface_IMG(pathFile);
	SDL_Surface* screenSurface = SDL_GetWindowSurface(*pWindow);

	fprintf(stderr, "Cheguei_load\n");

	surface = SDL_ConvertSurface(surface, screenSurface->format, 0);

	SDL_BlitSurface(surface, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(*pWindow);

	SDL_FreeSurface(surface);

	surface = NULL;
	screenSurface = NULL;

	return;
}

SDL_Surface* loadSurface_IMG(char* pathFile) {

	SDL_Surface* surface = NULL;
	surface = IMG_Load(pathFile);

	if(surface == NULL) {
		printf("Could not load image! Error: %s\n", IMG_GetError());
	}

	return surface;
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, char* pathFile) {

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

#endif