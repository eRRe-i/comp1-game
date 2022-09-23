#ifndef MAP
#define MAP

#include "common.h"
#include "textures.h"
#include "player.h"
#include "enemy.h"

typedef struct map {

    MapTexture* mapTexture;

    int mapId;

    Timer timer;
    float dt;

    int x;
    int y;
    
    int dstX;
    int dstY;

    SDL_Rect srcRect;
    SDL_Rect dstRect;

} Map;

Map* loadMapInitialState();
// void generateMaps(SDL_Renderer* renderer, Map **arrayMaps);
void geraMonstrosParaMapa(SDL_Renderer* renderer, Map* map);

#endif //MAP