#ifndef BACKGROUND
#define BACKGROUND

#include "common.h"
#define IMG_PATH "assets/gaia.jpeg"

typedef struct backgroundImage {
	
	SDL_Texture* backgroundImage;
	SDL_Rect displayRect;

	int width;
	int height;

} BackgroundImage;

typedef struct background {

	BackgroundImage backgroundImage;

} Background;

Background* loadBackground(SDL_Renderer* renderer);

#endif //BACKGROUND