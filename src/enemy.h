
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

} EnemyManager;

void generateEnemy(SDL_Renderer* renderer, Enemy* enemy, int type);
void updateEnemyFrame(Enemy* enemy);
void geraPosicao(int (*matrix)[70], Enemy *enemy);