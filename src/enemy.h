
#include "common.h"
#include "textures.h"

 
typedef struct enemy {
    
    int life;
    EnemyTexture *enemyTexture;
    int currentCharacterSide;

} Enemy;

void generateEnemy(SDL_Renderer* renderer, Enemy* enemy, int type);
