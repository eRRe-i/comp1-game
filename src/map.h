#ifndef MAP
#define MAP

#include "common.h"
#include "textures.h"
#include "player.h"
#include "enemy.h"

typedef struct map {

    int map_matrix[MATRIX_SIZE][MATRIX_SIZE];

    MapTexture* mapTexture;

    Timer timer;
    float dt;

    int x;
    int y;
    
    int dstX;
    int dstY;

    SDL_Rect srcRect;
    SDL_Rect dstRect;

    int id;
    int basicEnemy;
    int mediumEnemy;
    int highEnemy;
    int total_enemy;
    Enemy* Enemys[MAX_ENEMY_ARRAY];
} Map;

Map* loadMapInitialState();
int readmatrix(size_t rows, size_t cols, int (*a)[cols], int id);
void generateMaps(SDL_Renderer* renderer, Map **arrayMaps);
void geraMonstrosParaMapa(SDL_Renderer* renderer, Map* map);

#endif //MAP