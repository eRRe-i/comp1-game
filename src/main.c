#include "common.h"
#include "textures.h"
#include "player.h"
#include "map.h"
#include "map.h"
#include <stdbool.h>

int waiting(void);
void updateScreen(SDL_Renderer* renderer, Map* map, Player* player);
void updatePlayerState(Player* player, Map* map, KeyboardInput* keyboardInput);
void moveCharacter(Player* player, Map* map); 
void updateCharacterFrame(Player* player);
void updateDstBlock(Player* player, Map* map);
void updateScreen(SDL_Renderer* renderer, Map* map, CharacterTexture* character);
void updateMap(SDL_Renderer* renderer, Map* map);
void updateEnemy(SDL_Renderer* renderer, EnemyTexture* enemyTexture);
void cleanMap(Map* map);


bool loadFromRenderedText( const char* textureText, SDL_Color textColor, SDL_Renderer* gRenderer);

// int handleEvent(Player* Player, Background* background);
// variable declarations
SDL_Window *win = NULL;
SDL_Renderer *renderer = NULL;
CharacterTexture* characterTexture = NULL;
EnemyTexture* enemyTexture = NULL;
Map *mapas[MAP_LIST_SIZE];
int mapIndex = 0;
int actionFrame = 0;
SDL_RendererFlip flipType = SDL_FLIP_NONE;


int main (int argc, char *argv[])
//Image dimensions
int mWidth = 0;
int mHeight = 0;

TTF_Font *gFont = NULL;
SDL_Texture* font_texture = NULL;


bool loadMedia(SDL_Renderer* gRenderer);


int main (int argc, char *argv[]) 
{
	
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("ERROR : SDL Initialization > %s\n", SDL_GetError());
		return 1;
	}
	
	win = SDL_CreateWindow("Image Loading", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	generateMaps(renderer, mapas);

	updateMap(renderer, mapas[0]);
    characterTexture = loadCharacterTexture(renderer);

	MapTexture* mapTexture =  loadMapTexture(renderer);
    CharacterTexture* characterTexture = loadCharacterTexture(renderer);
	// enemyTexture = loadEnemyTexture(renderer,1);


	chdir("..");

	KeyboardInput* keyboardInput = loadKeyBoardInput();
	Player* player = loadPlayerInitialState(characterTexture);
	Map* map = loadMapInitialState(mapTexture);


	printf("Player moving: %i\n", player->isMoving);

	Timer t;
	t.currentTime = 0;

	// chdir("..");
	
	// main loop
	while (keyboardInput->gameStateKeyboardInput.quitGame == 0) {
	while (waiting()) {
        
		moveCharacter(characterTexture);
        updateScreen(renderer, mapas[mapIndex], characterTexture);

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
		else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F1){
			if(mapIndex > 0){
				// cleanMap(mapas[mapIndex]);
				mapIndex -= 1;
			}
		}
		else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F2){
			if(mapIndex < MAP_LIST_SIZE-1){
				// cleanMap(mapas[mapIndex]);
				mapIndex += 1;
			}
		}
		else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F3){
			actionFrame = 0;
		}
		else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F4){
			actionFrame = 1;
		}
		else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_q){
			flipType = SDL_FLIP_HORIZONTAL;
		}
	}
	return 1;
}
 
void updateScreen(SDL_Renderer* renderer, Map* map, CharacterTexture* character) {

        
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
        
		SDL_RenderClear(renderer);

		updateMap(renderer, map);

        SDL_RenderCopy	(renderer,
						character->characterSheet,
						&character->spritePosition[CHARACTER_FRONT][character->frame],
						&character->displayRect);

		SDL_RenderPresent(renderer);
}

void updateMap(SDL_Renderer* renderer, Map* map){
	if(map->mapTexture == NULL){
		readmatrix(MATRIX_SIZE,MATRIX_SIZE,map->matrix, map->id);
        map->mapTexture = loadMapTexture(renderer, map->id);
        geraMonstrosParaMapa(renderer, map);
	}

	SDL_RenderCopy(renderer,
		map->mapTexture->mapTexture,
		NULL,
		&map->mapTexture->displayRect);
	for(int i = 0; i < map->total_enemy; i++){
		updateEnemy(renderer, map->Enemys[i]->enemyTexture);
	}
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


void updateEnemy(SDL_Renderer* renderer, EnemyTexture* enemyTexture){
	moveEnemy(enemyTexture);
	SDL_RenderCopyEx(renderer, 
			enemyTexture->EnemySheet,
			&enemyTexture->spritePosition[actionFrame][enemyTexture->frame], 
			&enemyTexture->displayRect,
			0,
			NULL,
			flipType);
}

void cleanMap(Map* map){
	SDL_DestroyTexture(map->mapTexture->mapTexture);
	free(map->mapTexture);
	if(map->total_enemy < 100){
		for(int i = 0; i < map->total_enemy; i++){
			SDL_DestroyTexture(map->Enemys[i]->enemyTexture->EnemySheet);
			free(map->Enemys[i]->enemyTexture);
			free(map->Enemys[i]);
		}
	}
}