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

    //DESACLOPAR OS OBJETOS ASSOCIADOS AOS INIMIGOS. ESSA STRUCT VAI VIVER EM PHASEMANAGER
    int basicEnemy;
    int mediumEnemy;
    int highEnemy;
    int total_enemy;

    Enemy* Enemies[MAX_ENEMY_ARRAY];

} EnemyManager;

void generateEnemy(SDL_Renderer* renderer, Enemy* enemy, int type);
void updateEnemyFrame(Enemy* enemy);
void geraPosicao(int (*matrix)[70], Enemy *enemy);
EnemyManager* loadEnemyManager(int id);
void loadEnemies(SDL_Renderer* renderer, EnemyManager* enemyManager, int (*matrix)[70]);
void updateEnemiesPosition(EnemyManager* enemyManager, int x, int y);

#endif //ENE