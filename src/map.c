#include "common.h"
#include "textures.h"
#include "map.h"


Map* loadMapInitialState(MapTexture* mapTexture) {

    Map* map = (Map*)malloc(sizeof(Map));

    map->mapTexture = mapTexture;

    map->x = 320;
    map->y = 0;
    
    map->dstX = 320;
    map->dstY = 0;

    map->srcRect = fillRect(map->x, map->y, WINDOW_WIDTH, WINDOW_HEIGHT);
    map->dstRect = fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    return map;

}

