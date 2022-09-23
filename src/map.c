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


// void generateMaps(SDL_Renderer* renderer, Map **arrayMaps){
    
//     for(int i = 0; i< MAP_LIST_SIZE; i++){
//         int num = i+1;
        

//         arrayMaps[i] = loadMapInitialState();
//         arrayMaps[i]->id=num;
//         /*TODO: MELHORAR QTDE DE INIMIGOS*/
//         int randomMax = MIN_ENEMYS+(1*i);
//         arrayMaps[i]->basicEnemy = rand() % randomMax + MIN_ENEMYS;
//         arrayMaps[i]->mediumEnemy = 0;
//         arrayMaps[i]->highEnemy = 0;
//         arrayMaps[i]->total_enemy = (arrayMaps[i]->basicEnemy + arrayMaps[i]->mediumEnemy + arrayMaps[i]->highEnemy);
//         if(i != 0){
//             arrayMaps[i]->mediumEnemy = rand() % i;
//             arrayMaps[i]->highEnemy = rand() % i -1;
//         }
//         if(arrayMaps[i]->highEnemy <= 0)
//             arrayMaps[i]->highEnemy = 0;
//     }
// }