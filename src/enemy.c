
#include "common.h"
#include "enemy.h"
#include "textures.h"
#include <time.h>
/*
* TYPE = 1 -> BASIC_Enemy
* TYPE = 2 -> MEDIUM_Enemy
* TYPE = 3 -> HIGH_Enemy
*/

void generateEnemy(SDL_Renderer* renderer, Enemy* enemy, int type){
    
    if(type == 1)
        enemy->life = 10;
    if(type == 2)
        enemy->life = 20;
    if(type == 3)
        enemy->life = 30;
    
    enemy->moveSpeed = 2;    
    enemy->isMoving = TRUE;

    enemy->facingSide = CHARACTER_DOWN;
    enemy->frame = 1;
    enemy->moveMultiplier = 1;

    enemy->enemyTexture = loadEnemyTexture(renderer, type);
}
void geraPosicao(int (*matrix)[MATRIX_SIZE], Enemy *enemy){

    srand(time(0));
    int x = rand() % MATRIX_SIZE;
    int y = rand() % MATRIX_SIZE;

    while(matrix[x][y] != 0){
        x = rand() % MATRIX_SIZE;
        y = rand() % MATRIX_SIZE;
    }

    matrix[x][y] = ENEMY_MAP_ID;
    fprintf(stderr, "Enemy X: %i, Y: %i\n", x, y);
    enemy->boardIndex.i = x;
    enemy->boardIndex.j = y;
    enemy->enemyTexture->displayRect.x= x*MAP_DIM_X;
    enemy->enemyTexture->displayRect.y= y*MAP_DIM_Y;
}

EnemyManager* loadEnemyManager(int id){
    EnemyManager* enemyManager =  (EnemyManager*)malloc(sizeof(EnemyManager));
    int randomMax = MIN_Enemies+(2*id);
    int basic = rand() % randomMax + MIN_Enemies;
    if(id==0) id = 1;
    int medium = rand() % id;
    int high = rand() % id - 2;
    enemyManager->basicEnemy = basic;
    enemyManager->mediumEnemy = 0;
    enemyManager->highEnemy = 0;
    if(id != 0){
        enemyManager->mediumEnemy = medium;
        if(high>0)
            enemyManager->highEnemy = high;
    }
    enemyManager->total_enemy = (enemyManager->basicEnemy + enemyManager->mediumEnemy + enemyManager->highEnemy);
    for(int i=0; i< MAX_ENEMY_ARRAY; i++) {
        enemyManager->Enemies[i] = NULL;
    }
    return enemyManager;
}

void loadEnemies(SDL_Renderer* renderer, EnemyManager* enemyManager, int (*matrix)[MATRIX_SIZE]){
    fprintf(stderr, "BASIC: %i, MEDIO: %i, HIGH: %i\n",enemyManager->basicEnemy,enemyManager->mediumEnemy, enemyManager->highEnemy);
	for(int i = 0; i < enemyManager->basicEnemy; i++){
        enemyManager->Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
		generateEnemy(renderer,enemyManager->Enemies[i], 1);
        geraPosicao(matrix, enemyManager->Enemies[i]);
	}
	if(enemyManager->mediumEnemy > 0){
		for(int i = enemyManager->basicEnemy; i < (enemyManager->basicEnemy + enemyManager->mediumEnemy); i++){
            enemyManager->Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
			generateEnemy(renderer,enemyManager->Enemies[i], 2);
            geraPosicao(matrix, enemyManager->Enemies[i]);
		}
	}
	if(enemyManager->highEnemy > 0){
		for(int i = (enemyManager->basicEnemy + enemyManager->mediumEnemy); i < enemyManager->total_enemy; i++){
            enemyManager->Enemies[i] = (Enemy*)malloc(sizeof(Enemy));
			generateEnemy(renderer,enemyManager->Enemies[i], 3);
            geraPosicao(matrix, enemyManager->Enemies[i]);
		}
	}
}

/**
 * @brief Atualiza a posição x, y dos inimigos
 * 
 * @param enemyManager 
 * @param x 
 * @param y 
 */
void updateEnemyPosition(Enemy* enemy, int x, int y){
    enemy->enemyTexture->displayRect.x = x;
    enemy->enemyTexture->displayRect.y = y;
}