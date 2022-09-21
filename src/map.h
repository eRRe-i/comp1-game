#ifndef MAP
#define MAP

#include "common.h"
#include "textures.h"
#include "player.h"

typedef struct map {

    int map_matrix[70][70];

    MapTexture* mapTexture;

    Timer timer;
    float dt;

    int x;
    int y;
    
    int dstX;
    int dstY;

    SDL_Rect srcRect;
    SDL_Rect dstRect;
} Map;

Map* loadMapInitialState(MapTexture* mapTexture);

#endif //MAP