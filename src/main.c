#include "common.h"
#include "textures.h"
#include "player.h"
#include "map.h"

int waiting(void);
void updateScreen(SDL_Renderer* renderer, Map* map, Player* player);
void updatePlayerState(Player* player, Map* map, KeyboardInput* keyboardInput);
void moveCharacter(Player* player, Map* map); 
void updateCharacterFrame(Player* player);
void updateDstBlock(Player* player, Map* map);


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
	Map* map = loadMapInitialState(mapTexture);


	printf("Player moving: %i\n", player->isMoving);

	Timer t;
	t.currentTime = 0;

	// main loop
	while (keyboardInput->gameStateKeyboardInput.quitGame == 0) {

        map->timer.currentTime = map->timer.elapsedTime;
    	map->timer.elapsedTime = SDL_GetTicks();

		listenEvent(keyboardInput);
		updatePlayerState(player, map, keyboardInput);
        updateScreen(renderer, map, player);

		t.elapsedTime = SDL_GetTicks();
		if(t.elapsedTime - t.currentTime > 1000) {
			t.currentTime = t.elapsedTime;
			fprintf(stderr, "currentPoint: (%i, %i)\n dstPoint: (%i, %i)\n\n", map->x, map->y, map->dstX, map->dstY);
		}

	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	
	SDL_Quit();

	return 0;
}

void updateScreen(SDL_Renderer* renderer, Map* map, Player* player) {

        
        // clear the screen
		SDL_RenderClear(renderer);
		// copy the texture to the rendering context
		SDL_RenderCopy(	renderer, 
						map->mapTexture->mapTexture, 
						&map->srcRect,
						&map->dstRect);

        SDL_RenderCopy	(renderer, 
						player->characterTexture->characterSheet,
						&player->characterTexture->spritePosition[player->facingSide][player->frame], 
						&player->characterTexture->displayRect);
        

		SDL_RenderPresent(renderer);

}

void updatePlayerState(Player* player, Map* map, KeyboardInput* keyboardInput) {

	if(player->isMoving) {

		if(map->dstX == map->x && map->dstY == map->y) {

			if(keyboardInput->movePlayerKeyboardInput.moveInput != player->facingSide) {
				SDL_Log("case01");
				player->isMoving = TRUE;
				player->facingSide = keyboardInput->movePlayerKeyboardInput.moveInput;
				updateDstBlock(player, map);
				moveCharacter(player, map);
			} else if(keyboardInput->movePlayerKeyboardInput.moveInput == player->facingSide && keyboardInput->keyPressed) {
				SDL_Log("case02");
				player->isMoving = TRUE;
				player->facingSide = keyboardInput->movePlayerKeyboardInput.moveInput;
				updateDstBlock(player, map);
				moveCharacter(player, map);
			} else {
				SDL_Log("case03");
				player->isMoving = FALSE;
			}
		} else {
			SDL_Log("case04");
			moveCharacter(player, map);
			updateCharacterFrame(player);
		}
	} else {
		
		if(keyboardInput->keyReleased){
			return;
		} else if(player->facingSide == keyboardInput->movePlayerKeyboardInput.moveInput) {
			player->isMoving = TRUE;
			updateDstBlock(player, map);
			moveCharacter(player, map);
		
		} else if(player->facingSide != keyboardInput->movePlayerKeyboardInput.moveInput) {

			if(keyboardInput->keyReleased) {

			player->facingSide = keyboardInput->movePlayerKeyboardInput.moveInput;
			player->isMoving = FALSE;
			SDL_Delay(50);

			} else if (keyboardInput->keyPressed) {

				player->isMoving = TRUE;
				player->facingSide = keyboardInput->movePlayerKeyboardInput.moveInput;
				updateDstBlock(player, map);
				moveCharacter(player, map);
				
			}
		}
	}
	

}

void updateDstBlock(Player* player, Map* map) {


	switch(player->facingSide) {
		case CHARACTER_DOWN:{
						player->moveMultiplier = 1;
						map->dstY = map->y + BLOCKSIZE;
						break;
					}
		case CHARACTER_UP: {
						player->moveMultiplier = -1;
						map->dstY = map->y - BLOCKSIZE;
						break;
					}
		case CHARACTER_RIGHT: {
						player->moveMultiplier = +1;
						map->dstX = map->x + BLOCKSIZE;
						break;
					}
		case CHARACTER_LEFT: {
						player->moveMultiplier = -1;
						map->dstX = map->x - BLOCKSIZE;
						break;
					}
	}
}

void updateCharacterFrame(Player* player) {

	if(player->isMoving)
   		player->frame = (int)(SDL_GetTicks() / CHARACTER_FRAME_RATE)%4;
	else
		player->frame = 0; 

}

void moveCharacter(Player* player, Map* map) {


	if(map->x != map->dstX) {
		map->x += player->moveMultiplier * player->moveSpeed;
		map->srcRect = fillRect(map->x, map->y, WINDOW_WIDTH, WINDOW_HEIGHT);
	} else if (map->y != map->dstY) {
		map->y += player->moveMultiplier * player->moveSpeed;
		map->srcRect = fillRect(map->x, map->y, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}

