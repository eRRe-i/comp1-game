#include "common.h"
#include "textures.h"

#define MAP_DIM_X 32
#define MAP_DIM_Y 32

#define MAP_LIST_SIZE 10

typedef struct map {

	MapTexture * mapTexture;

    int matrix[35][35];
    int basicEnemy;
    int mediumEnemy;
    int highEnemy;


} Map;

int readmatrix(size_t rows, size_t cols, int (*a)[cols], const char* filename);

Map* generateMaps(SDL_Renderer* renderer);
