#include "common.h"
#include "textures.h"
#include "player.h"

int waiting(void);
void updateScreen(SDL_Renderer* renderer, MapTexture* map, Player* player);
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


	chdir("..");

	KeyboardInput* keyboardInput = loadKeyBoardInput();
	Player* player = loadPlayerInitialState(characterTexture);


	int flag = 0;

	printf("FACING SIDE: %i, FRAME: %i\n", player->facingSide, player->frame);
	printf("%p\n\n", &player->characterTexture->spritePosition[player->facingSide][player->frame].x);


	// main loop
	while (keyboardInput->gameStateKeyboardInput.quitGame == 0) {

        
		listenEvent(keyboardInput);
		if(flag==0) {
		printf("FACING SIDE: %i, FRAME: %i\n", player->facingSide, player->frame);
		printf("%p\n", &player->characterTexture->spritePosition[player->facingSide][player->frame].x);
		}
		updatePlayerState(player, keyboardInput);
		if(flag==0) {
		printf("FACING SIDE: %i, FRAME: %i\n", player->facingSide, player->frame);
		printf("%p\n", &player->characterTexture->spritePosition[player->facingSide][player->frame].x);
		}
        updateScreen(renderer, mapTexture, player);

		if(flag==0) {
			flag = 1;
		printf("FACING SIDE: %i, FRAME: %i\n", player->facingSide, player->frame);
		printf("%p\n", &player->characterTexture->spritePosition[player->facingSide][player->frame].x);
		}
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	
	SDL_Quit();

	return 0;
}

void updateScreen(SDL_Renderer* renderer, MapTexture* map, Player* player) {

                
        // clear the screen
		SDL_RenderClear(renderer);
		// copy the texture to the rendering context
		SDL_RenderCopy(	renderer, 
						map->mapTexture, 
						NULL, 
						&map->displayRect);

        SDL_RenderCopy	(renderer, 
						player->characterTexture->characterSheet,
						&player->characterTexture->spritePosition[player->facingSide][player->frame], 
						&player->characterTexture->displayRect);
        

		SDL_RenderPresent(renderer);

}
