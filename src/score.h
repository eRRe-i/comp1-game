#ifndef SCORE
#define SCORE

#include "common.h"
#include "textures.h"

 
typedef struct score {
    
    char score[100];
    int scoreValue;
    TTF_Font* fonte;
    SDL_Texture* texture;
    SDL_Surface* surface;
	SDL_Rect display;
    SDL_Color color;

} Score;


Score* loadScore(SDL_Renderer* renderer,TTF_Font* fonte, SDL_Color color);
void addScore(SDL_Renderer* renderer, Score* score, int valor);

#endif //ENE