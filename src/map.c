#include "common.h"
#include "textures.h"
#include "map.h"
#include "phaseManager.h"


Map* loadMapInitialState() {

    Map* map = (Map*)malloc(sizeof(Map));

    map->mapTexture = NULL;

    map->mapCurrentPosition.x = 320;
    map->mapCurrentPosition.y = 0;
    
    map->mapDestinationPosition.x = 320;
    map->mapDestinationPosition.y = 0;

    map->srcRect = fillRect(map->mapCurrentPosition.x,
                            map->mapCurrentPosition.y, 
                            WINDOW_WIDTH, 
                            WINDOW_HEIGHT);

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
