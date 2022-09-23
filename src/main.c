#include "common.h"
#include "textures.h"
#include "player.h"
#include "map.h"
#include "attack.h"
#include "enemy.h"
#include "phaseManager.h"
#include "board.h"

int waiting(void);
void updateScreen(SDL_Renderer* renderer, PhaseManager* phaseManager);
void updatePlayerState(PhaseManager* phaseManager, KeyboardInput* keyboardInput);
void moveCharacter(PhaseManager* phaseManager); 
void updateCharacterFrame(Player* player);
void updateDstBlock(PhaseManager* phaseManager);
void updateMap(SDL_Renderer* renderer, PhaseManager* phaseManager);
void updateEnemy(SDL_Renderer* renderer, Enemy* enemy);
void cleanMap(Map* map);
void moveEnemy(Enemy* enemy);
int checkIfObjectInsideRenderArea(SDL_Rect windowRenderArea, SDL_Rect ObjectRenderArea);
void renderEnemies(SDL_Renderer* renderer, PhaseManager* phaseManager);


int main (int argc, char *argv[])
{
	// variable declarations
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;

	
	int w, h; // texture width & height
	/**
	 * @brief Variável que muda o mapa a ser renderizado
	 * 
	 */
	int mapIndex = 0;
	
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("ERROR : SDL Initialization > %s\n", SDL_GetError());
		return 1;
	}
	
	win = SDL_CreateWindow("Image Loading", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	/**
	 * @brief Load informacoes de mapa
	 * 
	 */
	Map *mapas[MAP_LIST_SIZE];
	generateMaps(renderer, mapas);


    CharacterTexture* characterTexture = loadCharacterTexture(renderer);
	AttackTexture* firstAttackTexture = loadAttackTexture(renderer, FIRST_ATK_PATH, 40, 40);

	//chdir("..");

	KeyboardInput* keyboardInput = loadKeyBoardInput();
	Player* player = loadPlayerInitialState(characterTexture);
	AttackManager* attackManager = loadAttackManager();
	// Map* map = loadMapInitialState();

	PhaseManager* phaseManager = loadPhaseManager();
	Board* board = loadBoardInitialState(mapIndex);
	EnemyManager* enemyManager = loadEnemyManager(mapIndex);
	// fprintf(stderr, "\n\nTeste\n\n");

	phaseManager->map = mapas[mapIndex];
	phaseManager->player = player;
	phaseManager->attackManager = attackManager;
	phaseManager->board = board;
	phaseManager->enemyManager = enemyManager;

	phaseManager->attackManager->firstAttackTexture = firstAttackTexture;
	updateMap(renderer, phaseManager);
	loadEnemies(renderer, phaseManager->enemyManager, phaseManager->board->map_matrix);
	renderEnemies(renderer, phaseManager);

	Timer t;
	t.currentTime = 0;

	{
		phaseManager->attackManager->attackList[0] = loadAttack(phaseManager->attackManager->firstAttackTexture, 2, 2);
		
	}

	// main loop
	while (keyboardInput->gameStateKeyboardInput.quitGame == 0) {

        // mapas[mapIndex]->timer.currentTime = mapas[mapIndex]->timer.elapsedTime;
    	// mapas[mapIndex]->timer.elapsedTime = SDL_GetTicks();

		listenEvent(keyboardInput);
		updatePlayerState(phaseManager, keyboardInput);
		// if(keyboardInput->gameStateKeyboardInput.currentMapID != mapIndex){
		// 	mapIndex = keyboardInput->gameStateKeyboardInput.currentMapID;
		// 	phaseManager->map = mapas[mapIndex];
		// }
        updateScreen(renderer, phaseManager);


		t.elapsedTime = SDL_GetTicks();
		// if(t.elapsedTime - t.currentTime > 1000) {
		// 	t.currentTime = t.elapsedTime;
		// 	fprintf(stderr, "currentPoint: (%i, %i)\n dstPoint: (%i, %i)\n\n", mapas[mapIndex]->x, mapas[mapIndex]->y, mapas[mapIndex]->dstX, mapas[mapIndex]->dstY);
		// }

	}

	free(keyboardInput);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	
	SDL_Quit();

	return 0;
}

void updateScreen(SDL_Renderer* renderer, PhaseManager* phaseManager) {

		// Map* map = phaseManager->map;
		Player* player = phaseManager->player;
		AttackManager* attackManager = phaseManager->attackManager;
        
        // clear the screen
		SDL_RenderClear(renderer);
		// copy the texture to the rendering context
		// SDL_RenderCopy(	renderer, 
		// 				map->mapTexture->mapTexture, 
		// 				&map->srcRect,
		// 				&map->dstRect);

		updateMap(renderer, phaseManager);
		renderEnemies(renderer, phaseManager);

        SDL_RenderCopy	(renderer, 
						player->characterTexture->characterSheet,
						&player->characterTexture->spritePosition[player->facingSide][player->frame], 
						&player->characterTexture->displayRect);



		SDL_RenderCopy (renderer,
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
	int x = 0;
	int y = 0;
	if(map->x != map->dstX) {
		x = player->moveMultiplier * player->moveSpeed;
		map->x += x;
		map->srcRect = fillRect(map->x, map->y, WINDOW_WIDTH, WINDOW_HEIGHT);
	} else if (map->y != map->dstY) {
		y = player->moveMultiplier * player->moveSpeed;
		map->y += player->moveMultiplier * player->moveSpeed;
		map->srcRect = fillRect(map->x, map->y, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	// if(x != 0 || y != 0)
	// 	updateEnemiesPosition(phaseManager->enemyManager, x, y);
}
void updateMap(SDL_Renderer* renderer, PhaseManager* phaseManager){
	Map* map = phaseManager->map;
	if(map->mapTexture == NULL){
        map->mapTexture = loadMapTexture(renderer, map->id);
	}

	SDL_RenderCopy(renderer,
		map->mapTexture->mapTexture,
		&map->srcRect,
		&map->dstRect);
}

void updateEnemy(SDL_Renderer* renderer, Enemy* enemy){
	moveEnemy(enemy);
	fprintf(stderr, "ENEMY currentPoint: (%i, %i)\n", enemy->enemyTexture->displayRect.x, enemy->enemyTexture->displayRect.y);
	// enemy->enemyTexture->displayRect.x -=320;
	// enemy->enemyTexture->displayRect.y -=320;
	SDL_RenderCopy(renderer, 
			enemy->enemyTexture->Enemiesheet,
			&enemy->enemyTexture->spritePosition[enemy->facingSide][enemy->frame], 
			&enemy->enemyTexture->displayRect);
}

void moveEnemy(Enemy* enemy) {
    if(enemy->isMoving)
        enemy->frame = (int)(SDL_GetTicks() / CHARACTER_FRAME_RATE)%4;
}


int checkIfObjectInsideRenderArea(SDL_Rect windowRenderArea, SDL_Rect ObjectRenderArea) {

	int a = (ObjectRenderArea.x + ObjectRenderArea.w > windowRenderArea.x);
	int b = (ObjectRenderArea.y + ObjectRenderArea.h > windowRenderArea.y);
	int c = (windowRenderArea.x + windowRenderArea.w > ObjectRenderArea.x);
	int d = (windowRenderArea.y + windowRenderArea.h > ObjectRenderArea.y);

	return a && b && c && d;
}

void renderEnemies(SDL_Renderer* renderer, PhaseManager* phaseManager){
	for(int i = 0; i < phaseManager->enemyManager->total_enemy; i++){
		if(checkIfObjectInsideRenderArea(phaseManager->map->srcRect, phaseManager->enemyManager->Enemies[i]->enemyTexture->displayRect)){
			fprintf(stderr, "Vai printar\n");
			fprintf(stderr, "currentPoint: (%i, %i)\n", phaseManager->map->x, phaseManager->map->y);
			updateEnemy(renderer, phaseManager->enemyManager->Enemies[i]);
		}
	}
}

// void cleanMap(Map* map){
// 	SDL_DestroyTexture(map->mapTexture->mapTexture);
// 	free(map->mapTexture);
// 	if(map->total_enemy < 100){
// 		for(int i = 0; i < map->total_enemy; i++){
// 			SDL_DestroyTexture(map->Enemies[i]->enemyTexture->Enemiesheet);
// 			free(map->Enemies[i]->enemyTexture);
// 			free(map->Enemies[i]);
// 		}
// 	}
// }

void geraMonstrosParaMapa(SDL_Renderer* renderer, PhaseManager* phaseManager){

    Map* map = phaseManager->map;
    Board* board = phaseManager->board;
    EnemyManager* enemyManager = phaseManager->enemyManager;

    int size = enemyManager->total_enemy;
	for(int i = 0; i < enemyManager->basicEnemy; i++){
        enemyManager->Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
		generateEnemy(renderer,enemyManager->Enemies[i], 1);
        geraPosicao(board->map_matrix, enemyManager->Enemies[i]);
	}
	if(enemyManager->mediumEnemy > 0){
		for(int i = enemyManager->basicEnemy; i < (enemyManager->basicEnemy + enemyManager->mediumEnemy); i++){
            enemyManager->Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
			generateEnemy(renderer,enemyManager->Enemies[i], 2);
            geraPosicao(board->map_matrix, enemyManager->Enemies[i]);
		}
	}
	if(enemyManager->highEnemy > 0){
		for(int i = (enemyManager->basicEnemy + enemyManager->mediumEnemy); i < size; i++){
            enemyManager->Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
			generateEnemy(renderer,enemyManager->Enemies[i], 3);
            geraPosicao(board->map_matrix, enemyManager->Enemies[i]);
		}
	}
}