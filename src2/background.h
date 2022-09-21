#ifndef BACKGROUND
#define BACKGROUND

#include "common.h"
#define IMG_PATH "assets/Map1.png"

typedef struct backgroundImage {
	
	SDL_Texture* backgroundImage;
	SDL_Rect displayRect;

	int width;
	int height;
  
} BackgroundImage;

typedef struct background {

	BackgroundImage backgroundImage;

} Background;


#endif //BACKGROUND