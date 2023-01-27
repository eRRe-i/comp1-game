
#include "common.h"
#include "life.h"
#include "textures.h"


Life* loadLife(SDL_Renderer* renderer,int qtde){
    Life* life =  (Life*)malloc(sizeof(Life));
    life->boardIndex.i = 10;
    life->boardIndex.j = 10;
    for(int i=0; i< 5; i++) {
        life->lifes[i] = NULL;
        if(i<qtde)
           life->lifes[i] = loadLifeTexture(renderer, i);
    }
    life->frameLife = IMG_LoadTexture(renderer,  FRAME_PATH);
    return life;
}

