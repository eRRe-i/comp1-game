#include "common.h"
#include "textures.h"
#include "player.h"
#include "map.h"
#include "attack.h"
#include "enemy.h"
#include "phaseManager.h"
#include "board.h"
#include "life.h"
#include "score.h"
#include "menu.h"


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
void updateAttackPosition(PhaseManager* phaseManager);
void renderLife(SDL_Renderer* renderer, PhaseManager* phaseManager);
void renderScore(SDL_Renderer* renderer, PhaseManager* phaseManager);
Vector getPlayerPosition(PhaseManager* phaseManager);
void addLife(PhaseManager* phaseManager);
void reduzirLife(PhaseManager* phaseManager);
int checkIfEnemyHit(Board* board, int i, int j);
int updateEnemyHit(PhaseManager* phaseManager, BoardIndex board);
int updateIfPlayerHit(BoardIndex playerIndex, BoardIndex enemyIndex);


Timer t;
Timer t2;
char score[MAX_SIZE];
TTF_Font* fonteJogo = NULL;
TTF_Font* fonteBotao = NULL;
SDL_Color preto = {0, 0, 0};
SDL_Color branco = {255, 255, 255};

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
	if(TTF_Init() == -1){
    		SDL_Log("ERROR : SDL2_ttf não foi possível inicializar > %s\n", SDL_GetError());
	} else{
		SDL_Log("SDL2_ttf foi inicializado corretamente > %s\n", SDL_GetError());
	}

	win = SDL_CreateWindow("AA COMP 1", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	fonteJogo = TTF_OpenFont("fonts/IMMORTAL.ttf",128);
	
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	/**
	 * @brief Load informacoes de mapa
	 * 
	 */
	Map *mapas[MAP_LIST_SIZE];
	generateMaps(renderer, mapas);

    CharacterTexture* characterTexture = loadCharacterTexture(renderer);
	AttackTexture* firstAttackTexture = loadAttackTexture(renderer, FIRST_ATK_PATH);

	//chdir("..");
	Menu1* menu = loadMenu1(renderer);
	KeyboardInput* keyboardInput = loadKeyBoardInput();
	Player* player = loadPlayerInitialState(characterTexture);
	AttackManager* attackManager = loadAttackManager();

	PhaseManager* phaseManager = loadPhaseManager();
	Board* board = loadBoardInitialState(mapIndex);
	EnemyManager* enemyManager = loadEnemyManager(mapIndex);
	Life* life = loadLife(renderer, player->life);

	Score* score = loadScore(renderer, fonteJogo, branco);

	phaseManager->map = mapas[mapIndex];
	phaseManager->player = player;
	phaseManager->attackManager = attackManager;
	phaseManager->board = board;
	phaseManager->enemyManager = enemyManager;
	phaseManager->score = score;
	phaseManager->life = life;

	phaseManager->attackManager->firstAttackTexture = firstAttackTexture;
	loadEnemies(renderer, phaseManager->enemyManager, phaseManager->board->map_matrix);


	// for(int i = 0; i < 70; i++) {
	// 	for (int j = 0; j<70; j++) {

	// 		printf("%i ", phaseManager->board->map_matrix[i][j]);
	// 	}
	// 	printf("\n");
	// }

	fprintf(stderr, "menu->posCursor == %i\n", menu->posicaoCursor);

	t2.currentTime = 0;
	int saidaMenu = 0;
	// main loop
	while (keyboardInput->gameStateKeyboardInput.quitGame == 0) {

		if(saidaMenu == 0){
			saidaMenu = loopMenu1(renderer, menu);
		}
		if(saidaMenu == -1){
			keyboardInput->gameStateKeyboardInput.quitGame = 1;
		}
		if(saidaMenu==1){

			listenEvent(keyboardInput);
			updatePlayerState(phaseManager, keyboardInput);
			if(keyboardInput->gameStateKeyboardInput.currentMapID != mapIndex){
				mapIndex = keyboardInput->gameStateKeyboardInput.currentMapID;
				phaseManager->map = mapas[mapIndex];
				phaseManager->enemyManager = loadEnemyManager(mapIndex);
				loadEnemies(renderer, phaseManager->enemyManager, phaseManager->board->map_matrix);
				phaseManager->board = loadBoardInitialState(mapIndex);
			}
			// TODO: REMOVER QUANDO IMPLEMENTAR A LOGICA DE AUMENTAR O SCORE
			if(keyboardInput->gameStateKeyboardInput.score == 1){
				addScore(renderer, phaseManager->score, 10);
				keyboardInput->gameStateKeyboardInput.score = 0;
			}
			if(keyboardInput->gameStateKeyboardInput.addLife == 1){
				addLife(phaseManager);
				keyboardInput->gameStateKeyboardInput.addLife = 0;
			}
			if(keyboardInput->gameStateKeyboardInput.redLife == 1){
				reduzirLife(phaseManager);
				keyboardInput->gameStateKeyboardInput.redLife = 0;
			}
			updateAttackState(phaseManager, keyboardInput);
			updateScreen(renderer, phaseManager);
		
			/**
			 * @brief Atualiza o moviento do inimigo a cada 1 segundo
			 * 
			 */
			t.elapsedTime = SDL_GetTicks();
			if(t.elapsedTime - t.currentTime > 1000) {			
				t.currentTime = t.elapsedTime;
				moveEnemies(phaseManager);


				// BoardIndex b = getCharacterBoardIndex(phaseManager->map->mapCurrentPosition);
				// printf("%i - %i\n", b.i, b.j);
				// printf("Topo: %i | %i\n", checkIfWall(phaseManager->board, b.i-1, b.j), board->map_matrix[b.i-1][b.j]);
				// printf("Baixo:%i | %i\n", checkIfWall(phaseManager->board, b.i+1, b.j), board->map_matrix[b.i+1][b.j]);
				// printf("Dir:  %i | %i\n", checkIfWall(phaseManager->board, b.i, b.j+1), board->map_matrix[b.i][b.j+1]);
				// printf("Esq:  %i | %i\n\n", checkIfWall(phaseManager->board, b.i, b.j-1), board->map_matrix[b.i][b.j-1]);
				// fprintf(stderr, "board Index: (%i, %i)\n\n",
				// getCharacterBoardIndex(phaseManager->map->mapCurrentPosition).i,
				// getCharacterBoardIndex(phaseManager->map->mapCurrentPosition).j);

				// fprintf(stderr, "currentPoint: (%i, %i)\n\n", 
				// 		phaseManager->map->mapCurrentPosition.x, 
				// 		phaseManager->map->mapCurrentPosition.y);
			}

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
		renderEnemies(renderer, phaseManager);
		renderAttacks(renderer, phaseManager);
		updateAttackPosition(phaseManager);
		renderScore(renderer, phaseManager);
		renderLife(renderer, phaseManager);
		
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
	
	//se está se movendo
	if(player->isMoving) {

		//se chegou no destino
		if(map->mapDestinationPosition.x == map->mapCurrentPosition.x && map->mapDestinationPosition.y == map->mapCurrentPosition.y) {
			
			// se um keydown está é uma key diferente
			if(keyboardInput->movePlayerKeyboardInput.currentInput != keyboardInput->movePlayerKeyboardInput.previousInput && keyboardInput->keyPressed) {
			
				player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;

				//se o move é válido
				if(checkIfPlayerMoveIsValid(phaseManager)) {
					player->isMoving = TRUE;
					updateDstBlock(phaseManager);
					moveCharacter(phaseManager);

					// SDL_Log("Case01");

				}
			//se a keydown é a mesma key
			} else if(keyboardInput->movePlayerKeyboardInput.currentInput == keyboardInput->movePlayerKeyboardInput.previousInput && keyboardInput->keyPressed) {

				player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
				//se o move é válido
				if(checkIfPlayerMoveIsValid(phaseManager)) {

					player->isMoving = TRUE;
					updateDstBlock(phaseManager);
					moveCharacter(phaseManager);
					// SDL_Log("Case02");
			
				}
			// se não há key pressionada no frame
			} else {
				player->isMoving = FALSE;
			}
		//se ainda não chegou no destino
		} else {

			moveCharacter(phaseManager);
			updateCharacterFrame(phaseManager->player);
			// SDL_Log("Case03");
		}
		
	//se não está se movendo
	} else {
		
		//se qualquer key está solta
		if(keyboardInput->keyReleased){
			return;

		//se triggar o ataque
		// } else if (keyboardInput->attackKeyboardInput.attack == FIRST_ATTACK){
		// 	SDL_Log("Case 04");
		// 	updateAttackState(phaseManager, keyboardInput);
		// 	SDL_Delay(200);
		
		//se o input atual for pro mesmo lado do personagem
		}else if(player->facingSide == keyboardInput->movePlayerKeyboardInput.currentInput) {
			
			//se o move é válido
			if(checkIfPlayerMoveIsValid(phaseManager)) {

				player->isMoving = TRUE;
				updateDstBlock(phaseManager);
				moveCharacter(phaseManager);

			}
		//se o input é pra um lado diferente;
		} else if(player->facingSide != keyboardInput->movePlayerKeyboardInput.currentInput && keyboardInput->keyPressed) {

			if(keyboardInput->movePlayerKeyboardInput.currentInput >= 0){
				player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
				player->isMoving = FALSE;

			}				

		//se for outro move que não o input de move
		} else if (keyboardInput->movePlayerKeyboardInput.currentInput == player->facingSide && keyboardInput->keyPressed) {
				
			player->facingSide = keyboardInput->movePlayerKeyboardInput.currentInput;
				
			//se o move é válido
			if(checkIfPlayerMoveIsValid(phaseManager)) {

				player->isMoving = TRUE;
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

		if(phaseManager->enemyManager->Enemies[i] != NULL) {
			Enemy * enemy = phaseManager->enemyManager->Enemies[i];
			if(checkIfObjectInsideRenderArea(phaseManager->map->srcRect, enemy->enemyTexture->displayRect)){
				moveEnemy(enemy, phaseManager);
			}
			if(updateIfPlayerHit(getCharacterBoardIndex(phaseManager->map->mapCurrentPosition), enemy->boardIndex)) {
				enemy = NULL;
				phaseManager->player->life -= 1;
			}
		
		}
	}
}

void moveEnemy(Enemy* enemy, PhaseManager *phaseManager) {
	int x = rand() %2;
	int frenteTraz = rand() %2;
	if(x == 0){
		if(frenteTraz == 0){
			if(phaseManager->board->map_matrix[enemy->boardIndex.i -1][enemy->boardIndex.j] == 0)
				phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j] = 0;
				enemy->boardIndex.i -= 1;
		}else{
			if(phaseManager->board->map_matrix[enemy->boardIndex.i +1][enemy->boardIndex.j] == 0)
				phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j] = 0;
				enemy->boardIndex.i += 1;
		}
		phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j] = 3;
	}else{
		if(frenteTraz == 0){
			if(phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j -1] == 0)
				phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j] = 0;
				enemy->boardIndex.j -= 1;
		}else{
			if(phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j + 1] == 0)
				phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j] = 0;
				enemy->boardIndex.j += 1;
		}
		phaseManager->board->map_matrix[enemy->boardIndex.i][enemy->boardIndex.j] = 3;

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
		if (enemy != NULL) {
			if(checkIfObjectInsideRenderArea(phaseManager->map->srcRect, enemy->enemyTexture->displayRect)){
				Vector newPosition = getObjectViewPosfromGlobalPos(map->mapCurrentPosition, getGlobalPositionFromBoardIndex(enemy->boardIndex));
				updateEnemy(renderer, enemy, newPosition);
			}

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

	index.i = mapCurrentPosition.y / 32 + 10;
	index.j = mapCurrentPosition.x / 32 + 12;

	return index;
}

int checkIfPlayerMoveIsValid(PhaseManager*phaseManager) {

	Board* board = phaseManager->board;
	Player* player = phaseManager->player;

	BoardIndex playerIndex = getCharacterBoardIndex(phaseManager->map->mapCurrentPosition);

	int isValid;

	switch(player->facingSide) {
		case CHARACTER_DOWN: { 
			isValid = !checkIfWall(board, playerIndex.i+1, playerIndex.j);
			break;
		}
		case CHARACTER_UP: {
			isValid = !checkIfWall(board, playerIndex.i-1, playerIndex.j);
			break;
		}
		case CHARACTER_LEFT: {
			isValid = !checkIfWall(board, playerIndex.i, playerIndex.j-1);
			break;
		}
		case CHARACTER_RIGHT: {
			isValid = !checkIfWall(board, playerIndex.i, playerIndex.j+1);
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
	Attack* attack;

	int reachedDestination = map->mapDestinationPosition.x == map->mapCurrentPosition.x && map->mapDestinationPosition.y == map->mapCurrentPosition.y;

	if(reachedDestination && keyboardInput->attackKeyboardInput.attack == FIRST_ATTACK) {

		fprintf(stderr,"ATAQUE STATE\n");
		if(checkValidAttack(phaseManager)) {
			// getGlobalPositionFromBoardIndex
			BoardIndex playerIndex = getCharacterBoardIndex(phaseManager->map->mapCurrentPosition);
			BoardIndex attackIndex;
			Vector playerGlobalPosition = getGlobalPositionFromBoardIndex(playerIndex);
			Vector attackMove = setVector(0,0);
			Vector attackInitialPosition;
			Vector attackGlobalPosition;
			// fprintf(stderr, "PlayerBoardIndex I: %i, J: %i\n", playerIndex.i, playerIndex.j);
			// fprintf(stderr, "PlayerGlobalPossition  X: %i, Y: %i\n\n", playerGlobalPosition.x, playerGlobalPosition.y);
			// fprintf(stderr, "FACE SIDE %i", player->facingSide);

			switch(player->facingSide) {

				case CHARACTER_DOWN:{
					fprintf(stderr, "ENTROU BAIXO\n");
					attackGlobalPosition = setVector(playerGlobalPosition.x,playerGlobalPosition.y + BLOCKSIZE);
					attackInitialPosition = getObjectViewPosfromGlobalPos(map->mapCurrentPosition, attackGlobalPosition);
					attackMove = setVector(0, ATTACK_SPEED);
					attackIndex = setBoardIndex(playerIndex.i-1,playerIndex.j);
					break;
				}
				case CHARACTER_UP: {
					fprintf(stderr, "ENTROU CIMA\n");
					attackGlobalPosition = setVector(playerGlobalPosition.x,playerGlobalPosition.y - BLOCKSIZE);
					attackInitialPosition = getObjectViewPosfromGlobalPos(map->mapCurrentPosition, attackGlobalPosition);
					attackMove = setVector(0, -ATTACK_SPEED);
					attackIndex = setBoardIndex(playerIndex.i-1, playerIndex.j);
					break;
				}
				case CHARACTER_RIGHT: {
					fprintf(stderr, "ENTROU DIREITA\n");
					attackGlobalPosition = setVector(playerGlobalPosition.x + BLOCKSIZE, playerGlobalPosition.y);
					attackInitialPosition = getObjectViewPosfromGlobalPos(map->mapCurrentPosition, attackGlobalPosition);
					attackMove = setVector(ATTACK_SPEED, 0);
					attackIndex = setBoardIndex(playerIndex.i,playerIndex.j+1);

					break;
				}
				case CHARACTER_LEFT: {
					fprintf(stderr, "ENTROU ESQUERDA\n");
					attackGlobalPosition = setVector(playerGlobalPosition.x - BLOCKSIZE, playerGlobalPosition.y);
					attackInitialPosition = getObjectViewPosfromGlobalPos(map->mapCurrentPosition, attackGlobalPosition);
					attackMove = setVector(-ATTACK_SPEED, 0);
					attackIndex = setBoardIndex(playerIndex.i,playerIndex.j-1);
					break;
				}
			}
			// fprintf(stderr, "AttackBoardIndex:    I: %i, J: %i \n", attackIndex.i, attackIndex.j);
			// fprintf(stderr, "AttackBoardPosition: X: %i, J: %i\n\n", attackInitialPosition.x, attackInitialPosition.y);

			for(int i = 0; i < 5; i++) {
				if (attackManager->attackList[i] == NULL) {
					fprintf(stderr,"gerando ataque\n");
					attack = loadAttack(attackManager->firstAttackTexture,
										attackInitialPosition,
										attackGlobalPosition,
										attackMove);
					attackManager->attackList[i] =	attack;
					break;
				}
			}
		}
		keyboardInput->attackKeyboardInput.attack = 0;
		// renderAttacks(renderer, phaseManager);
	}

}

void updateAttackPosition(PhaseManager* phaseManager){
	AttackManager* attackManager = phaseManager->attackManager;
	Board* board = phaseManager->board;
	// fprintf(stderr, "update\n");
	for(int i = 0; i < 5; i++) {
		if(attackManager->attackList[i] != NULL) {
			Attack* attack = attackManager->attackList[i];
			SDL_Rect renderRect = 	{	attack->attackPosition.x,
										attack->attackPosition.y,
										BLOCKSIZE,
										BLOCKSIZE
									};
			BoardIndex attackIndex = getBoardIndexFromGlobalPosition(attack->globalPosition);
			// fprintf(stderr, "(%i, %i)\n", attackIndex.i, attackIndex.j);
			// fprintf(stderr, "Wall: %i\n", checkIfWall(board, attackIndex.i, attackIndex.j));
			// fprintf(stderr, "Wall? %i\n\n", board->map_matrix[attackIndex.i][attackIndex.j]);
			if(!checkIfObjectInsideRenderArea(phaseManager->map->dstRect, renderRect)) {

				fprintf(stderr,"APAGANDO ataque %i\n", i);
				attackManager->attackList[i]=NULL;

			} else if(checkIfWall(board, attackIndex.i, attackIndex.j)){
				
				fprintf(stderr,"APAGANDO ataque %i\n", i);
				attackManager->attackList[i]=NULL;

			} else if (checkIfEnemyHit(board, attackIndex.i, attackIndex.j)) {
				
				if(updateEnemyHit(phaseManager, attackIndex)) {
					fprintf(stderr,"APAGANDO ataque %i\n", i);
					attackManager->attackList[i] = NULL;
					fprintf(stderr,"CHEGUEI\n");
				}

			} else {
				attack->attackPosition.x += attack->attackMovement.x;
				attack->attackPosition.y += attack->attackMovement.y;
				attack->globalPosition.x += attack->attackMovement.x;
				attack->globalPosition.y += attack->attackMovement.y;
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
void renderLife(SDL_Renderer* renderer, PhaseManager* phaseManager){
	Vector playerPosition = getPlayerPosition(phaseManager);
	Vector lifePosition = setVector(playerPosition.x-400,playerPosition.y -335);
	Vector newPosition = getObjectViewPosfromGlobalPos(phaseManager->map->mapCurrentPosition, lifePosition);
	for(int i = 0;i<phaseManager->player->life;i++){

		if(phaseManager->life->lifes[i] == NULL)
			phaseManager->life->lifes[i] = loadLifeTexture(renderer, i);
		phaseManager->life->lifes[i]->displayRect.x = phaseManager->life->lifes[i]->x + newPosition.x;
		phaseManager->life->lifes[i]->displayRect.y = phaseManager->life->lifes[i]->y + newPosition.y;
		SDL_RenderCopy(renderer, 
				phaseManager->life->lifes[i]->texture,
				&phaseManager->life->lifes[i]->spritePosition[0][0], 
				&phaseManager->life->lifes[i]->displayRect);
	}
}

void renderScore(SDL_Renderer* renderer, PhaseManager* phaseManager){

	if(phaseManager->score->update == 1){
			fprintf(stderr,"ADD SCORE\n");
		addScore(renderer, phaseManager->score, phaseManager->score->scoreValue);
		phaseManager->score->update = 0;
	}


	Vector playerPosition = getPlayerPosition(phaseManager);
	Vector renderPosition = setVector(playerPosition.x+300,playerPosition.y-315);
	Vector newPosition = getObjectViewPosfromGlobalPos(phaseManager->map->mapCurrentPosition, renderPosition);
	phaseManager->score->display.x = newPosition.x;
	phaseManager->score->display.y = newPosition.y;
	SDL_RenderCopy(renderer, phaseManager->score->texture, NULL, &phaseManager->score->display);

}
Vector getPlayerPosition(PhaseManager* phaseManager){
	
	BoardIndex playerIndex = getCharacterBoardIndex(phaseManager->map->mapCurrentPosition);
	return getGlobalPositionFromBoardIndex(playerIndex);
}
void reduzirLife(PhaseManager* phaseManager){
	if(phaseManager->player->life > 0)
		phaseManager->player->life -=1;	
}
void addLife(PhaseManager* phaseManager){
	if(phaseManager->player->life < 5 )
		phaseManager->player->life +=1;	
}

int checkIfEnemyHit(Board* board, int i, int j) {

	return board->map_matrix[i][j] == 3;
}

int updateEnemyHit(PhaseManager* phaseManager, BoardIndex board) {

	EnemyManager* enemyManager = phaseManager->enemyManager;
	int a, b;

	for(int i=0; i< phaseManager->enemyManager->total_enemy; i++) {

		if(enemyManager->Enemies[i] != NULL) {
			
			a = enemyManager->Enemies[i]->boardIndex.i == board.i;
			b = enemyManager->Enemies[i]->boardIndex.j == board.j;
			if(a && b) {
				printf("%i, %i\n", board.i, enemyManager->Enemies[i]->boardIndex.i);
				printf("%i, %i\n", board.j, enemyManager->Enemies[i]->boardIndex.j);
				enemyManager->Enemies[i] = NULL;
				if(phaseManager->player->life >0 && phaseManager->player->life < 5)
					phaseManager->player->life += 1;
				phaseManager->score->scoreValue += 200;
				phaseManager->score->update = 1;
				return TRUE;
			}
		}

	}
	return FALSE;
}
int updateIfPlayerHit(BoardIndex playerIndex, BoardIndex enemyIndex) {

	int pointI = playerIndex.i == enemyIndex.j;
	int pointJ = playerIndex.j == enemyIndex.j;

	return pointI && pointJ;

}
