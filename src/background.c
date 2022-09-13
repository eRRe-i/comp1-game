#include "background.h"

Background* loadBackground(SDL_Renderer* renderer) {

	Background* background = (Background*)malloc(sizeof(Background));

	background->backgroundImage.backgroundImage = loadImage(renderer, IMG_PATH);
	
	SDL_QueryTexture(background->backgroundImage.backgroundImage, NULL, NULL, &background->backgroundImage.width, &background->backgroundImage.height);

	background->backgroundImage.displayRect.x = 0;
	background->backgroundImage.displayRect.y = 0;
	background->backgroundImage.displayRect.w = background->backgroundImage.width;
	background->backgroundImage.displayRect.h = background->backgroundImage.height;

	return background;
}