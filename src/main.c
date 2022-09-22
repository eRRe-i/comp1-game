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
void updateMap(SDL_Renderer* renderer, Map* map);
void updateEnemy(SDL_Renderer* renderer, Enemy* enemy);
void cleanMap(Map* map);
void moveEnemy(Enemy* enemy);


int main (int argc, char *argv[])
{
	// variable declarations
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;

	
	int w, h; // texture width & height
	int mapIndex = 0;
	
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("ERROR : SDL Initialization > %s\n", SDL_GetError());
		return 1;
	}
	
	win = SDL_CreateWindow("Image Loading", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Map *mapas[MAP_LIST_SIZE];
	generateMaps(renderer, mapas);

	updateMap(renderer, mapas[mapIndex]);

	// MapTexture* mapTexture =  loadMapTexture(renderer);
    CharacterTexture* characterTexture = loadCharacterTexture(renderer);


	//chdir("..");

	KeyboardInput* keyboardInput = loadKeyBoardInput();
	Player* player = loadPlayerInitialState(characterTexture);
	// Map* map = loadMapInitialState(mapTexture);


	printf("Player moving: %i\n", player->isMoving);

	Timer t;
	t.currentTime = 0;

	// main loop
	while (keyboardInput->gameStateKeyboardInput.quitGame == 0) {
		fprintf(stderr, "inicio do while\n");
        mapas[mapIndex]->timer.currentTime = mapas[mapIndex]->timer.elapsedTime;
    	mapas[mapIndex]->timer.elapsedTime = SDL_GetTicks();
		fprintf(stderr, "SDL_GetTicks\n");
		listenEvent(keyboardInput);
		updatePlayerState(player, mapas[mapIndex], keyboardInput);
        updateScreen(renderer, mapas[mapIndex], player);
		fprintf(stderr, "updates\n");
		t.elapsedTime = SDL_GetTicks();
		if(t.elapsedTime - t.currentTime > 1000) {
			t.currentTime = t.elapsedTime;
			fprintf(stderr, "currentPoint: (%i, %i)\n dstPoint: (%i, %i)\n\n", mapas[mapIndex]->x, mapas[mapIndex]->y, mapas[mapIndex]->dstX, mapas[mapIndex]->dstY);
		}

	}

	free(keyboardInput);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	
	SDL_Quit();

	return 0;
}

void updateScreen(SDL_Renderer* renderer, Map* map, Player* player) {

        
        // clear the screen
		SDL_RenderClear(renderer);
		// copy the texture to the rendering context
		// SDL_RenderCopy(	renderer, 
		// 				map->mapTexture->mapTexture, 
		// 				&map->srcRect,
		// 				&map->dstRect);

		updateMap(renderer, map);

        SDL_RenderCopy	(renderer, 
						player->characterTexture->characterSheet,
						&player->characterTexture->spritePosition[player->facingSide][player->frame], 
						&player->characterTexture->displayRect);
        

		SDL_RenderPresent(renderer);

}

void updatePlayerState(Player* player, Map* map, KeyboardInput* keyboardInput) {

	if(player->isMoving) {

		if(map->dstX == map->x && map->dstY == map->y) {
			if(keyboardInput->keyReleased){
				player->isMoving = FALSE;
			} else if(keyboardInput->movePlayerKeyboardInput.currentInput != keyboardInput->movePlayerKeyboardInput.previousInput) {
				player->isMoving = TRUE;
				player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
				updateDstBlock(player, map);
				moveCharacter(player, map);
			} else if(keyboardInput->movePlayerKeyboardInput.currentInput == keyboardInput->movePlayerKeyboardInput.previousInput && keyboardInput->keyPressed) {
				player->isMoving = TRUE;
				player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
				updateDstBlock(player, map);
				moveCharacter(player, map);
			}
			
		} else {
			moveCharacter(player, map);
			updateCharacterFrame(player);
		}
	} else {
		
		if(keyboardInput->keyReleased){
			return;
		} else if(player->facingSide == keyboardInput->movePlayerKeyboardInput.currentInput) {
			player->isMoving = TRUE;
			updateDstBlock(player, map);
			moveCharacter(player, map);
		
		} else if(player->facingSide != keyboardInput->movePlayerKeyboardInput.currentInput) {

			if(keyboardInput->keyReleased) {

			player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
			player->isMoving = FALSE;

			} else if (keyboardInput->keyPressed) {

				player->isMoving = TRUE;
				player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
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
void updateMap(SDL_Renderer* renderer, Map* map){
	if(map->mapTexture == NULL){
		fprintf(stderr, "TEXTURA MAP NULL\n");
		readmatrix(MATRIX_SIZE,MATRIX_SIZE,map->map_matrix, map->id);
        map->mapTexture = loadMapTexture(renderer, map->id);
        geraMonstrosParaMapa(renderer, map);
		fprintf(stderr, "FIM TEXTURA MAP NULL\n");
	}

	SDL_RenderCopy(renderer,
		map->mapTexture->mapTexture,
		NULL,
		&map->mapTexture->displayRect);
	fprintf(stderr, "UPDATE INIMIGOS\n");
	for(int i = 0; i < map->total_enemy; i++){
		updateEnemy(renderer, map->Enemys[i]);
	}
	fprintf(stderr, "FIM UPDATE INIMIGOS\n");
}

void updateEnemy(SDL_Renderer* renderer, Enemy* enemy){
	moveEnemy(enemy);
	SDL_RenderCopyEx(renderer, 
			enemy->enemyTexture->EnemySheet,
			&enemy->enemyTexture->spritePosition[enemy->facingSide][enemy->frame], 
			&enemy->enemyTexture->displayRect,
			0,
			NULL,
			SDL_FLIP_NONE);
}

void moveEnemy(Enemy* enemy) {
    if(enemy->isMoving)
        enemy->frame = (int)(SDL_GetTicks() / CHARACTER_FRAME_RATE)%4;
}

// void cleanMap(Map* map){
// 	SDL_DestroyTexture(map->mapTexture->mapTexture);
// 	free(map->mapTexture);
// 	if(map->total_enemy < 100){
// 		for(int i = 0; i < map->total_enemy; i++){
// 			SDL_DestroyTexture(map->Enemys[i]->enemyTexture->EnemySheet);
// 			free(map->Enemys[i]->enemyTexture);
// 			free(map->Enemys[i]);
// 		}
// 	}
// }