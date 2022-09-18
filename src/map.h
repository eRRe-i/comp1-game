#include "common.h"
#include "textures.h"
#include "enemy.h"

#define MAP_DIM_X 32
#define MAP_DIM_Y 32

#define MAP_LIST_SIZE 10
#define MATRIX_SIZE 70

typedef struct map {

	MapTexture * mapTexture;

    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int basicEnemy;
    int mediumEnemy;
    int highEnemy;
    Enemy* Enemys[100];


} Map;

int readmatrix(size_t rows, size_t cols, int (*a)[cols], const char* filename);

void generateMaps(SDL_Renderer* renderer, Map **arrayMaps);
void geraMonstrosParaMapa(SDL_Renderer* renderer, Map* map);//int basicEnemy, int mediumEnemy, int highEnemy );
