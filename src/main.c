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
void updateEnemy(SDL_Renderer* renderer, Enemy* enemy, Vector newPosition);
void cleanMap(Map* map);
void moveEnemy(Enemy* enemy, PhaseManager *phaseManager);
int checkIfObjectInsideRenderArea(SDL_Rect windowRenderArea, SDL_Rect ObjectRenderArea);
void renderEnemies(SDL_Renderer* renderer, PhaseManager* phaseManager);
void setPlayerPosition(PhaseManager* phaseManager);
Vector getGlobalPositionFromBoardIndex(BoardIndex boardIndex);
Vector getObjectViewPosfromGlobalPos(Vector viewPos, Vector globalPos);
BoardIndex getCharacterBoardIndex(Vector mapCurrentPosition);

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
	loadEnemies(renderer, phaseManager->enemyManager, phaseManager->board->map_matrix);
	// updateMap(renderer, phaseManager);
	

	Timer t;
	t.currentTime = 0;

	// {
	// 	phaseManager->attackManager->attackList[0] = loadAttack(phaseManager->attackManager->firstAttackTexture, 2, 2);
		
	// }

	// main loop
	while (keyboardInput->gameStateKeyboardInput.quitGame == 0) {

        // mapas[mapIndex]->timer.currentTime = mapas[mapIndex]->timer.elapsedTime;
    	// mapas[mapIndex]->timer.elapsedTime = SDL_GetTicks();

		listenEvent(keyboardInput);
		updatePlayerState(phaseManager, keyboardInput);
		if(keyboardInput->gameStateKeyboardInput.currentMapID != mapIndex){
			mapIndex = keyboardInput->gameStateKeyboardInput.currentMapID;
			phaseManager->map = mapas[mapIndex];
			phaseManager->enemyManager = loadEnemyManager(mapIndex);
			loadEnemies(renderer, phaseManager->enemyManager, phaseManager->board->map_matrix);
			phaseManager->board = loadBoardInitialState(mapIndex);
		}
        updateScreen(renderer, phaseManager);


		t.elapsedTime = SDL_GetTicks();
		if(t.elapsedTime - t.currentTime > 10000) {
			t.currentTime = t.elapsedTime;
			// renderEnemies(renderer, phaseManager);
		// 	fprintf(stderr, "currentPoint: (%i, %i)\n dstPoint: (%i, %i)\n", 
		// 					phaseManager->map->mapCurrentPosition.x, 
		// 					phaseManager->map->mapCurrentPosition.y,
		// 					phaseManager->map->mapDestinationPosition.x, 
		// 					phaseManager->map->mapDestinationPosition.y);
		// 	fprintf(stderr, "board Index: (%i, %i)\n\n",
		// 					getCharacterBoardIndex(phaseManager->map->mapCurrentPosition).i,
		// 					getCharacterBoardIndex(phaseManager->map->mapCurrentPosition).j);
		}

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
		Timer t;
		t.currentTime = 0;
		t.elapsedTime = int(SDL_GetTicks() / CHARACTER_FRAME_RATE) %4;
		fprintf(stderr, "tempo = %i", t.elapsedTime);
		// if(t.elapsedTime - t.currentTime > 10000) {
		// 	t.currentTime = t.elapsedTime;
		// }
        SDL_RenderCopy	(renderer, 
						player->characterTexture->characterSheet,
						&player->characterTexture->spritePosition[player->facingSide][player->frame], 
						&player->characterTexture->displayRect);



		// SDL_RenderCopy (renderer,
		// 			attackManager->attackList[0]->atkTexture->texture,
		// 			NULL,
		// 			&attackManager->attackList[0]->dstRect);

        

		SDL_RenderPresent(renderer);
}


// int attackPositionIsValid(Board* board, int board_x, int board_y) {

// 	if(board->map_matrix[board_x][board_y] == IMMOVABLE_BOARD_ID) {
// 		return FALSE;
// 	} else {
// 		return TRUE;
// 	}
// }

// void checkValidAttack(PhaseManager* phaseManager, KeyboardInput* keyboardInput) {

// 	Player* player = phaseManager->player;
// 	Board* board = phaseManager->board;

// 	if(keyboardInput->attackKeyboardInput.attack == FIRST_ATTACK) {

// 		switch(player->facingSide) {

// 			case CHARACTER_DOWN: {

// 				if(attackPositionIsValid(p))
// 			}
// 		}
// 	}

// }

void updatePlayerState(PhaseManager* phaseManager, KeyboardInput* keyboardInput) {

	Map* map = phaseManager->map;
	Player* player = phaseManager->player;

	if(player->isMoving) {

		if(map->mapDestinationPosition.x == map->mapCurrentPosition.x && map->mapDestinationPosition.y == map->mapCurrentPosition.y) {
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
			SDL_Delay(100);

			} else if (keyboardInput->keyPressed && keyboardInput->movePlayerKeyboardInput.currentInput != NO_KEYBOARD_INPUT) {

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
						map->mapDestinationPosition.y = map->mapCurrentPosition.y + BLOCKSIZE;
						break;
					}
		case CHARACTER_UP: {
						player->moveMultiplier = -1;
						map->mapDestinationPosition.y = map->mapCurrentPosition.y - BLOCKSIZE;
						break;
					}
		case CHARACTER_RIGHT: {
						player->moveMultiplier = +1;
						map->mapDestinationPosition.x = map->mapCurrentPosition.x + BLOCKSIZE;
						break;
					}
		case CHARACTER_LEFT: {
						player->moveMultiplier = -1;
						map->mapDestinationPosition.x = map->mapCurrentPosition.x - BLOCKSIZE;
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
	if(map->mapCurrentPosition.x != map->mapDestinationPosition.x) {
		player->movementVector = setVector(player->moveMultiplier * player->moveSpeed, 0);
		map->mapCurrentPosition = addVector(map->mapCurrentPosition, player->movementVector);
		map->srcRect = fillRect(map->mapCurrentPosition.x, map->mapCurrentPosition.y, WINDOW_WIDTH, WINDOW_HEIGHT);
	} else if (map->mapCurrentPosition.y != map->mapDestinationPosition.y) {
		player->movementVector = setVector(0, player->moveMultiplier * player->moveSpeed);
		map->mapCurrentPosition = addVector(map->mapCurrentPosition, player->movementVector);
		map->srcRect = fillRect(map->mapCurrentPosition.x, map->mapCurrentPosition.y, WINDOW_WIDTH, WINDOW_HEIGHT);
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

void updateEnemy(SDL_Renderer* renderer, Enemy* enemy, Vector newPosition){
	// fprintf(stderr, "ENEMY currentPoint: (%i, %i)\n", enemy->enemyTexture->displayRect.x, enemy->enemyTexture->displayRect.y);
	// enemy->enemyTexture->displayRect.x -=320;
	// enemy->enemyTexture->displayRect.y -=320;
	SDL_Rect renderRect = {newPosition.x, newPosition.y, enemy->enemyTexture->displayRect.w,enemy->enemyTexture->displayRect.h}; 
	SDL_RenderCopy(renderer, 
			enemy->enemyTexture->Enemiesheet,
			&enemy->enemyTexture->spritePosition[enemy->facingSide][enemy->frame], 
			&renderRect);
}

void moveEnemy(Enemy* enemy, PhaseManager *phaseManager) {
	int x = rand() %2;
	int frenteTraz = rand() %2;
	if(x == 0){
		if(frenteTraz == 0)
			if(phaseManager->board->map_matrix[enemy->boardIndex.i -1][enemy->boardIndex.j] == 0)
				enemy->boardIndex.i -= 1;
			// else if(phaseManager->board->map_matrix[enemy->boardIndex.i +1][enemy->boardIndex.j] == 0)
			// 	enemy->boardIndex.i += 1;
		else{
			if(phaseManager->board->map_matrix[enemy->boardIndex.i +1][enemy->boardIndex.j] == 0)
				enemy->boardIndex.i += 1;
			// else if(phaseManager->board->map_matrix[enemy->boardIndex.i -1][enemy->boardIndex.j] == 0)
			// 	enemy->boardIndex.i -= 1;
		}
	}else{
		if(frenteTraz == 0)
			if(phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j -1] == 0)
				enemy->boardIndex.j -= 1;
			// else if(phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j +1] == 0)
			// 	enemy->boardIndex.j += 1;
		else{
			if(phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j + 1] == 0)
				enemy->boardIndex.j += 1;
			// else if(phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j -1] == 0)
			// 	enemy->boardIndex.j -= 1;
		}
	}

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

	Map* map = phaseManager->map;

	for(int i = 0; i < phaseManager->enemyManager->total_enemy; i++){
		Enemy * enemy = phaseManager->enemyManager->Enemies[i];
		if(checkIfObjectInsideRenderArea(phaseManager->map->srcRect, enemy->enemyTexture->displayRect)){
			Vector newPosition = getObjectViewPosfromGlobalPos(map->mapCurrentPosition, getGlobalPositionFromBoardIndex(enemy->boardIndex));
			updateEnemy(renderer, enemy, newPosition);
			// moveEnemy(enemy, phaseManager);
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

Vector getGlobalPositionFromBoardIndex(BoardIndex boardIndex) {

	Vector vector;

	vector.x = boardIndex.i *32;
	vector.y = boardIndex.j *32;

	return vector;
}


BoardIndex getCharacterBoardIndex(Vector mapCurrentPosition) {

	BoardIndex index;

	index.i = mapCurrentPosition.x / 32 + 13;
	index.j = mapCurrentPosition.y / 32 + 11;

	return index;
}

Vector getObjectViewPosfromGlobalPos(Vector viewPos, Vector globalPos) {

	Vector vector;

	vector.x = globalPos.x - viewPos.x;
	vector.y = globalPos.y - viewPos.y;

	return vector;
}