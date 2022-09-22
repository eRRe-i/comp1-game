
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

void generateEnemy(SDL_Renderer* renderer, Enemy* enemy, int type);
void updateEnemyFrame(Enemy* enemy);
void geraPosicao(int (*matrix)[70], Enemy *enemy);