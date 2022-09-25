
#include "common.h"
#include "score.h"
#include "textures.h"


Score* loadScore(SDL_Renderer* renderer,TTF_Font* fonte, SDL_Color color){
    Score* score =  (Score*)malloc(sizeof(Score));
    score->scoreValue = 0;
    score->fonte = fonte;
    score->color = color;
    addScore(renderer, score, 0);    
    score->display.x =0;
    score->display.y =0;
    score->display.w =100;
    score->display.h =40;
    return score;
}
void addScore(SDL_Renderer* renderer, Score* score, int valor){
    score->scoreValue +=valor;
    char scoreText[100];
    sprintf(scoreText, "SCORE: %i",score->scoreValue);
    score->surface = TTF_RenderText_Solid(score->fonte,scoreText, score->color);
	score->texture = SDL_CreateTextureFromSurface(renderer, score->surface);
}
