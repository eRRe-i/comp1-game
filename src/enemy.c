
#include "common.h"
#include "enemy.h"
#include "textures.h"

/*
* TYPE = 1 -> BASIC_Enemy
* TYPE = 2 -> MEDIUM_Enemy
* TYPE = 3 -> HIGH_Enemy
*/

EnemyManager* loadEnemyManager() {

    EnemyManager* enemyManager = (EnemyManager*)malloc(sizeof(EnemyManager));

    for(int i=0; i< MAX_ENEMY_ARRAY; i++) {

        enemyManager->Enemies[i] = NULL;
    }

    return EnemyManager;
}

void generateEnemy(SDL_Renderer* renderer, Enemy* enemy, int type){
    
    if(type == 1){
        enemy->life = 10;
        enemy->moveSpeed = 2;
    }
    if(type == 2){
        enemy->life = 20;
        enemy->moveSpeed = 2;
    }
    if(type == 3){
        enemy->life = 30;
        enemy->moveSpeed = 2;
    }
    
    enemy->isMoving = TRUE;

    enemy->facingSide = CHARACTER_DOWN;
    enemy->frame = 1;
    enemy->moveMultiplier = 1;

    enemy->enemyTexture = loadEnemyTexture(renderer, type);
}
void geraPosicao(int (*matrix)[MATRIX_SIZE], Enemy *enemy){

    int x = rand() % MATRIX_SIZE;
    int y = rand() % MATRIX_SIZE;

    while(matrix[x][y] != 0){
        x = rand() % MATRIX_SIZE;
        y = rand() % MATRIX_SIZE;
    }

    matrix[x][y] = 1;
    enemy->enemyTexture->displayRect.x= x*MAP_DIM_X;
    enemy->enemyTexture->displayRect.y= y*MAP_DIM_Y;
}
