#ifndef LIFE
#define LIFE

#include "common.h"
#include "textures.h"

 
typedef struct life {
    
    LifeTexture *lifes[5];
    
    SDL_Texture* frameLife;
    BoardIndex boardIndex;
} Life;


Life* loadLife(SDL_Renderer* renderer, int qtde);

#endif //ENE