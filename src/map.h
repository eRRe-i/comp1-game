#ifndef MAP
#define MAP

#include "common.h"
#include "textures.h"
#include "player.h"

typedef struct map {

    MapTexture* mapTexture;

    int mapId;

    Timer timer;
    float dt;


    Vector mapCurrentPosition; 
    Vector mapDestinationPosition;


    SDL_Rect srcRect;
    SDL_Rect dstRect;

    int id;
} Map;

Map* loadMapInitialState();
void generateMaps(SDL_Renderer* renderer, Map **arrayMaps);


#endif //MAP