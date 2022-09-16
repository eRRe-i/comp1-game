#include "common.h"
#include "textures.h"

int waiting(void);
void updateScreen(SDL_Renderer* renderer, MapTexture* map, CharacterTexture* character);
// int handleEvent(Player* Player, Background* background);

int main (int argc, char *argv[])
{
	// variable declarations
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;

	
	int w, h; // texture width & height
	
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("ERROR : SDL Initialization > %s\n", SDL_GetError());
		return 1;
	}
	
	win = SDL_CreateWindow("Image Loading", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


	MapTexture* mapTexture =  loadMapTexture(renderer);
    CharacterTexture* characterTexture = loadCharacterTexture(renderer);
	// mapTexture->mapTexture = loadMap(renderer);
	// characterTexture->characterSheet = loadCharacter(renderer);

	chdir("..");

	
	// main loop
	while (waiting()) {
        
		moveCharacter(characterTexture);
        updateScreen(renderer, mapTexture, characterTexture);

	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	
	SDL_Quit();

	return 0;
}

int waiting(void)
{
	// event handling
	SDL_Event e;
	if(SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return 0;
		else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
			return 0;
	}
	return 1;
}

void updateScreen(SDL_Renderer* renderer, MapTexture* map, CharacterTexture* character) {

                
        // clear the screen
		SDL_RenderClear(renderer);
		// copy the texture to the rendering context
		SDL_RenderCopy(	renderer, 
						map->mapTexture, 
						NULL, 
						&map->displayRect);
		// flip the backbuffer  
		// this means that everything that we prepared behind the screens is actually shown
        SDL_RenderCopy	(renderer, 
						character->characterSheet,
						&character->spritePosition[CHARACTER_FRONT][character->frame], 
						&character->displayRect);
        

		SDL_RenderPresent(renderer);

}
