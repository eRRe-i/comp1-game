#include "common.h"
#include "textures.h"
#include "map.h"
#include "phaseManager.h"


Map* loadMapInitialState() {

    Map* map = (Map*)malloc(sizeof(Map));

    map->mapTexture = NULL;

    map->x = 320;
    map->y = 0;
    
    map->dstX = 320;
    map->dstY = 0;

    map->srcRect = fillRect(map->x, map->y, WINDOW_WIDTH, WINDOW_HEIGHT);
    map->dstRect = fillRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    return map;

}

void generateMaps(SDL_Renderer* renderer, Map **arrayMaps){
    
    for(int i = 0; i< MAP_LIST_SIZE; i++){
        int num = i+1;
        arrayMaps[i] = loadMapInitialState();
        arrayMaps[i]->id=num;
    }
}
