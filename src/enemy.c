
#include "common.h"
#include "enemy.h"
#include "textures.h"

/*
* TYPE = 1 -> BASIC_Enemy
* TYPE = 2 -> MEDIUM_Enemy
* TYPE = 3 -> HIGH_Enemy
*/
void generateEnemy(SDL_Renderer* renderer,Enemy* enemy, int type){
    enemy->life = 10;
    enemy->enemyTexture = loadEnemyTexture(renderer, type );
}

