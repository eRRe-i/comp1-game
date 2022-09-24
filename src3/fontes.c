#include "fontes.h"

Fontes* loadFontesInitialState(){
    Fontes* fontes = (Fontes*)malloc(sizeof(Fontes));
    //Carregar arquivo fonte e setar o tamanho
	fontes->fonteJogo = TTF_OpenFont("./fonts/KarmaFuture.ttf",16);
	fontes->fonteScore = TTF_OpenFont("./fonts/ka1.ttf",16);
	fontes->fonteRecord = TTF_OpenFont("./fonts/ArcadeClassic.ttf",32);
    // fontes->preto = (SDL_Color)malloc(sizeof(SDL_Color));
    fontes->preto = (struct SDL_Color){0,0,0,255};
    fontes->branco = (struct SDL_Color){255,255,255,255};
	// fontes->preto.r = 0;
    // fontes->preto.g = 0;
    // fontes->preto.b = 0;
    // fontes->preto.a = 255;
    // fontes->branco.r = 255;
    // fontes->branco.g = 255;
    // fontes->branco.b = 255;
    // fontes->branco.a = 255;

    //confirmar que foi carregado
	if(fontes->fonteJogo == NULL){
		SDL_Log("ERROR : Não foi possível carregar a fonte > %s\n", SDL_GetError());
		exit(1);
	}
    return fontes;
}