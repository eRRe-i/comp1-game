#include "common.h"
#include "textures.h"
#include "player.h"
#include "map.h"
#include "attack.h"
#include "phaseManager.h"

int waiting(void);
void updateScreen(SDL_Renderer* renderer, PhaseManager* phaseManager);
void updatePlayerState(PhaseManager* phaseManager, KeyboardInput* keyboardInput);
void moveCharacter(PhaseManager* phaseManager); 
void updateCharacterFrame(Player* player);
void updateDstBlock(PhaseManager* phaseManager);


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
	AttackTexture* firstAttackTexture = loadAttackTexture(renderer, FIRST_ATK_PATH, 40, 40);


	chdir("..");

	KeyboardInput* keyboardInput = loadKeyBoardInput();
	Player* player = loadPlayerInitialState(characterTexture);
	Map* map = loadMapInitialState(mapTexture);
	AttackManager* attackManager = loadAttackManager();
	PhaseManager* phaseManager = loadPhaseManager();


	phaseManager->map = map;
	phaseManager->player = player;
	phaseManager->attackManager = attackManager;

	phaseManager->attackManager->firstAttackTexture = firstAttackTexture;

	printf("Player moving: %i\n", player->isMoving);

	Timer t;
	t.currentTime = 0;

	{
		phaseManager->attackManager->attackList[0] = loadAttack(phaseManager->attackManager->firstAttackTexture, 2, 2);
		
	}

	// main loop
	while (keyboardInput->gameStateKeyboardInput.quitGame == 0) {

        map->timer.currentTime = map->timer.elapsedTime;
    	map->timer.elapsedTime = SDL_GetTicks();

		listenEvent(keyboardInput);
		updatePlayerState(phaseManager, keyboardInput);
        updateScreen(renderer, phaseManager);

		

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

void updateScreen(SDL_Renderer* renderer, PhaseManager* phaseManager) {

		Map* map = phaseManager->map;
		Player* player = phaseManager->player;
		AttackManager* attackManager = phaseManager->attackManager;
        
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


		
			SDL_RenderCopy (	renderer,
								attackManager->attackList[0]->atkTexture->texture,
								NULL,
								&attackManager->attackList[0]->dstRect);
		
        

		SDL_RenderPresent(renderer);

}

void updatePlayerState(PhaseManager* phaseManager, KeyboardInput* keyboardInput) {

	Map* map = phaseManager->map;
	Player* player = phaseManager->player;

	if(player->isMoving) {

		if(map->dstX == map->x && map->dstY == map->y) {
			if(keyboardInput->keyReleased){
				player->isMoving = FALSE;
			} else if(keyboardInput->movePlayerKeyboardInput.currentInput != keyboardInput->movePlayerKeyboardInput.previousInput) {
				player->isMoving = TRUE;
				player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
				updateDstBlock(phaseManager);
				moveCharacter(phaseManager);
			} else if(keyboardInput->movePlayerKeyboardInput.currentInput == keyboardInput->movePlayerKeyboardInput.previousInput && keyboardInput->keyPressed) {
				player->isMoving = TRUE;
				player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
				updateDstBlock(phaseManager);
				moveCharacter(phaseManager);
			}
			
		} else {
			moveCharacter(phaseManager);
			updateCharacterFrame(phaseManager->player);
		}
	} else {
		
		if(keyboardInput->keyReleased){
			return;
		} else if(player->facingSide == keyboardInput->movePlayerKeyboardInput.currentInput) {
			player->isMoving = TRUE;
			updateDstBlock(phaseManager);
			moveCharacter(phaseManager);
		
		} else if(player->facingSide != keyboardInput->movePlayerKeyboardInput.currentInput) {

			if(keyboardInput->keyReleased) {

			player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
			player->isMoving = FALSE;

			} else if (keyboardInput->keyPressed) {

				player->isMoving = TRUE;
				player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
				updateDstBlock(phaseManager);
				moveCharacter(phaseManager);
				
			}
		}
	}
	

}

void updateDstBlock(PhaseManager* phaseManager) {

	Map* map = phaseManager->map;
	Player* player = phaseManager->player;

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

void moveCharacter(PhaseManager* phaseManager) {

	Map* map = phaseManager->map;
	Player* player = phaseManager->player;

	if(map->x != map->dstX) {
		map->x += player->moveMultiplier * player->moveSpeed;
		map->srcRect = fillRect(map->x, map->y, WINDOW_WIDTH, WINDOW_HEIGHT);
	} else if (map->y != map->dstY) {
		map->y += player->moveMultiplier * player->moveSpeed;
		map->srcRect = fillRect(map->x, map->y, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}
