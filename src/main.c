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
BoardIndex getCharacterBoardIndex(Vector mapCurrentPosition);
int checkIfPlayerMoveIsValid(PhaseManager* phaseManager);
int checkIfWall(Board* board, int i, int j);
void moveEnemies(PhaseManager* phaseManager);
void updateFrameEnemy(Enemy* enemy);
void updateAttackState(PhaseManager* phaseManager, KeyboardInput* keyboardInput);
void renderAttacks(SDL_Renderer* renderer, PhaseManager* phaseManager);
int checkValidAttack(PhaseManager* phaseManager);

Timer t;

int main (int argc, char *argv[])
{
	// variable declarations
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	
	t.currentTime = 0;
	
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
	AttackTexture* firstAttackTexture = loadAttackTexture(renderer, FIRST_ATK_PATH);

	//chdir("..");

	KeyboardInput* keyboardInput = loadKeyBoardInput();
	Player* player = loadPlayerInitialState(characterTexture);
	AttackManager* attackManager = loadAttackManager();

	PhaseManager* phaseManager = loadPhaseManager();
	Board* board = loadBoardInitialState(mapIndex);
	EnemyManager* enemyManager = loadEnemyManager(mapIndex);

	phaseManager->map = mapas[mapIndex];
	phaseManager->player = player;
	phaseManager->attackManager = attackManager;
	phaseManager->board = board;
	phaseManager->enemyManager = enemyManager;

	phaseManager->attackManager->firstAttackTexture = firstAttackTexture;
	loadEnemies(renderer, phaseManager->enemyManager, phaseManager->board->map_matrix);

	// main loop
	while (keyboardInput->gameStateKeyboardInput.quitGame == 0) {

		listenEvent(keyboardInput);
		updateAttackState(phaseManager, keyboardInput);
		updatePlayerState(phaseManager, keyboardInput);
		if(keyboardInput->gameStateKeyboardInput.currentMapID != mapIndex){
			mapIndex = keyboardInput->gameStateKeyboardInput.currentMapID;
			phaseManager->map = mapas[mapIndex];
			phaseManager->enemyManager = loadEnemyManager(mapIndex);
			loadEnemies(renderer, phaseManager->enemyManager, phaseManager->board->map_matrix);
			phaseManager->board = loadBoardInitialState(mapIndex);
		}
        updateScreen(renderer, phaseManager);

		/**
		 * @brief Atualiza o moviento do inimigo a cada 1 segundo
		 * 
		 */
		t.elapsedTime = SDL_GetTicks();
		if(t.elapsedTime - t.currentTime > 1000) {			
			t.currentTime = t.elapsedTime;
			moveEnemies(phaseManager);
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

		Player* player = phaseManager->player;
		AttackManager* attackManager = phaseManager->attackManager;

		SDL_RenderClear(renderer);

		updateMap(renderer, phaseManager);
		renderAttacks(renderer, phaseManager);
		renderEnemies(renderer, phaseManager);
        SDL_RenderCopy(renderer,
			player->characterTexture->characterSheet,
			&player->characterTexture->spritePosition[player->facingSide][player->frame],
			&player->characterTexture->displayRect);

		SDL_RenderPresent(renderer);
}

void updatePlayerState(PhaseManager* phaseManager, KeyboardInput* keyboardInput) {

	Map* map = phaseManager->map;
	Player* player = phaseManager->player;

	int reachedDestination = map->mapDestinationPosition.x == map->mapCurrentPosition.x && map->mapDestinationPosition.y == map->mapCurrentPosition.y;


	if(player->isMoving) {

		if(map->mapDestinationPosition.x == map->mapCurrentPosition.x && map->mapDestinationPosition.y == map->mapCurrentPosition.y) {
		
				if(keyboardInput->movePlayerKeyboardInput.currentInput != keyboardInput->movePlayerKeyboardInput.previousInput) {
				
					player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;

					if(checkIfPlayerMoveIsValid(phaseManager)) {
						player->isMoving = TRUE;
						updateDstBlock(phaseManager);
						moveCharacter(phaseManager);

					}

				} else if(keyboardInput->movePlayerKeyboardInput.currentInput == keyboardInput->movePlayerKeyboardInput.previousInput && keyboardInput->keyPressed) {

					player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
					if(checkIfPlayerMoveIsValid(phaseManager)) {

						player->isMoving = TRUE;
						updateDstBlock(phaseManager);
						moveCharacter(phaseManager);

					}
				} else if(keyboardInput->keyReleased){
					player->isMoving = FALSE;
				}
			 
		} else {
			moveCharacter(phaseManager);
			updateCharacterFrame(phaseManager->player);
		}
	} else {
		
		if(keyboardInput->keyReleased){
			return;

		} else if(player->facingSide == keyboardInput->movePlayerKeyboardInput.currentInput) {
			
			if(checkIfPlayerMoveIsValid(phaseManager)) {

				player->isMoving = TRUE;
				updateDstBlock(phaseManager);
				moveCharacter(phaseManager);

			}
			
		} else if(player->facingSide != keyboardInput->movePlayerKeyboardInput.currentInput) {

			if(keyboardInput->keyReleased) {

			player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
			player->isMoving = FALSE;

			} else if (keyboardInput->keyPressed && keyboardInput->movePlayerKeyboardInput.currentInput != NO_KEYBOARD_INPUT) {
				
				player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
				
				
				if(checkIfPlayerMoveIsValid(phaseManager)) {

				player->isMoving = TRUE;
				updateDstBlock(phaseManager);
				moveCharacter(phaseManager);

				}
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
	updateFrameEnemy(enemy);
	SDL_Rect renderRect = {newPosition.x, newPosition.y, enemy->enemyTexture->displayRect.w,enemy->enemyTexture->displayRect.h}; 
	SDL_RenderCopy(renderer, 
			enemy->enemyTexture->Enemiesheet,
			&enemy->enemyTexture->spritePosition[enemy->facingSide][enemy->frame], 
			&renderRect);
}

void moveEnemies(PhaseManager* phaseManager){
	for(int i = 0; i < phaseManager->enemyManager->total_enemy; i++){
		Enemy * enemy = phaseManager->enemyManager->Enemies[i];
		if(checkIfObjectInsideRenderArea(phaseManager->map->srcRect, enemy->enemyTexture->displayRect)){
			moveEnemy(enemy, phaseManager);
		}
	}
}

void moveEnemy(Enemy* enemy, PhaseManager *phaseManager) {
	int x = rand() %2;
	int frenteTraz = rand() %2;
	if(x == 0){
		if(frenteTraz == 0){
			if(phaseManager->board->map_matrix[enemy->boardIndex.i -1][enemy->boardIndex.j] == 0)
				enemy->boardIndex.i -= 1;
		}else{
			if(phaseManager->board->map_matrix[enemy->boardIndex.i +1][enemy->boardIndex.j] == 0)
				enemy->boardIndex.i += 1;
		}
	}else{
		if(frenteTraz == 0){
			if(phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j -1] == 0)
				enemy->boardIndex.j -= 1;
		}else{
			if(phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j + 1] == 0)
				enemy->boardIndex.j += 1;
		}
	}
}

void updateFrameEnemy(Enemy* enemy){
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


BoardIndex getCharacterBoardIndex(Vector mapCurrentPosition) {

	BoardIndex index;

	index.i = mapCurrentPosition.x / 32 + 13;
	index.j = mapCurrentPosition.y / 32 + 11;

	return index;
}

int checkIfPlayerMoveIsValid(PhaseManager*phaseManager) {

	Board* board = phaseManager->board;
	Player* player = phaseManager->player;

	BoardIndex playerIndex = getCharacterBoardIndex(phaseManager->map->mapCurrentPosition);

	int isValid;

	switch(player->facingSide) {
		case CHARACTER_DOWN: { 
			isValid = !checkIfWall(board, playerIndex.i, playerIndex.j + 1);
			break;
		}
		case CHARACTER_UP: {
			isValid = !checkIfWall(board, playerIndex.i, playerIndex.j - 1);
			break;
		}
		case CHARACTER_LEFT: {
			isValid = !checkIfWall(board, playerIndex.i - 1, playerIndex.j);
			break;
		}
		case CHARACTER_RIGHT: {
			isValid = !checkIfWall(board, playerIndex.i + 1, playerIndex.j);
			break;
		}
	}

	return isValid;
}

int checkIfWall(Board* board, int i, int j) {

	return board->map_matrix[i][j] == IMMOVABLE_MAP_ID;
}


void updateAttackState(PhaseManager* phaseManager, KeyboardInput* keyboardInput) {

	AttackManager* attackManager = phaseManager->attackManager;
	Map* map = phaseManager->map;
	Player* player = phaseManager->player;

	int reachedDestination = map->mapDestinationPosition.x == map->mapCurrentPosition.x && map->mapDestinationPosition.y == map->mapCurrentPosition.y;

	if(reachedDestination && keyboardInput->attackKeyboardInput.attack == FIRST_ATTACK) {

		if(checkValidAttack(phaseManager)) {

			BoardIndex playerIndex = getCharacterBoardIndex(phaseManager->map->mapCurrentPosition);
			BoardIndex attackIndex;
			Vector playerGlobalPosition = getGlobalPositionFromBoardIndex(playerIndex);
			Vector attackInitialPosition;
			Vector attackMove;

			switch(player->facingSide) {

				case CHARACTER_DOWN:{	
					attackInitialPosition = setVector(	playerGlobalPosition.x,
														playerGlobalPosition.y + BLOCKSIZE);
					attackMove = setVector(0, 2 * 1);
					attackIndex = setBoardIndex(	playerIndex.i,
													playerIndex.j + 1);
					break;
				}
				case CHARACTER_UP: {
					attackInitialPosition = setVector(	playerGlobalPosition.x,
														playerGlobalPosition.y + BLOCKSIZE);
					attackMove = setVector(0, 2 * -1);
					attackIndex = setBoardIndex(	playerIndex.i,
													playerIndex.j - 1);	
					break;
				}
				case CHARACTER_RIGHT: {
					attackInitialPosition = setVector(	playerGlobalPosition.x + BLOCKSIZE,
														playerGlobalPosition.y);
					attackMove = setVector(2 * 1, 0);
					attackIndex = setBoardIndex(	playerIndex.i + 1,
													playerIndex.j);
					break;
				}
				case CHARACTER_LEFT: {
					attackInitialPosition = setVector(	playerGlobalPosition.x + BLOCKSIZE,
														playerGlobalPosition.y);
					attackMove = setVector(2 * -1, 0);
					attackIndex = setBoardIndex(	playerIndex.i-1,
													playerIndex.j);
					break;
				}
			}

			for(int i = 0; i < 5; i++) {

				if (attackManager->attackList[i] == NULL) {
					
					attackManager->attackList[i] =	loadAttack(	attackManager->firstAttackTexture,
												attackInitialPosition,
												attackMove,
												attackIndex);
					break;
				}
			}
		}
	}

}

void renderAttacks(SDL_Renderer* renderer, PhaseManager* phaseManager) {

	AttackManager* attackManager = phaseManager->attackManager;

	for(int i = 0; i < 5; i++) {
		if(attackManager->attackList[i] != NULL) {

			Attack* attack = attackManager->attackList[i];
		
			SDL_Rect renderRect = 	{	attack->attackPosition.x,
										attack->attackPosition.y,
										BLOCKSIZE,
										BLOCKSIZE
									};

			SDL_RenderCopy(	renderer,
							attackManager->attackList[i]->atkTexture->texture,
							NULL,
							&renderRect
							);
		}
	}
	return;

}

int checkValidAttack(PhaseManager* phaseManager) {

	return checkIfPlayerMoveIsValid(phaseManager);

}