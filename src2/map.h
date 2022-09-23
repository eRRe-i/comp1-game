#include "common.h"
#include "textures.h"
#include "enemy.h"


typedef struct map {

	MapTexture * mapTexture;
    int id;
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int basicEnemy;
    int mediumEnemy;
    int highEnemy;
    int total_enemy;
    int state;
    Enemy* Enemies[MAX_ENEMY_ARRAY];

} Map;

int readmatrix(size_t rows, size_t cols, int (*a)[cols], int id);

void generateMaps(SDL_Renderer* renderer, Map **arrayMaps);
void geraMonstrosParaMapa(SDL_Renderer* renderer, Map* map);
