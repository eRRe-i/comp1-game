#ifndef ENEMY
#define ENEMY

#include "common.h"
#include "textures.h"

 
typedef struct enemy {
    
    int life;
	int isMoving;
    float moveSpeed;

    int facingSide;
    int frame;
    int moveMultiplier;

    EnemyTexture *enemyTexture;
} Enemy;


typedef struct enemyManager {

    int basicEnemy;
    int mediumEnemy;
    int highEnemy;
    int total_enemy;

    Enemy* Enemies[MAX_ENEMY_ARRAY];

} EnemyManager;

EnemyManager* loadEnemyManager();
void generateEnemy(SDL_Renderer* renderer, Enemy* enemy, int type);
void updateEnemyFrame(Enemy* enemy);
void geraPosicao(int (*matrix)[70], Enemy *enemy);

#endif //ENEMY