#ifndef DEBUG
#define DEBUG
#include "common.h"
#include <stdbool.h>

typedef struct menu1{
    int posicaoCursor;
    SDL_Texture *fundo;
    SDL_Texture *nomejogo;
    SDL_Texture *texturaBotao;
    SDL_Texture *texturaTexto;
    SDL_Texture *texturaPlay;
    SDL_Texture *texturaOpcao;
    SDL_Texture *texturaInstrucao;
    SDL_Texture *texturaRanking;
    SDL_Texture *texturaCreditos;
    SDL_Texture *texturaSair;
    SDL_Texture *texturaSeta;
    SDL_Texture* texturaVolta;
    SDL_Texture* texturaScore;

    SDL_Surface *superficieFundo;
	SDL_Surface *superficieBotao;
	SDL_Surface *superficieTexto;
	SDL_Surface *superficiePlay;
	SDL_Surface *superficieOpcao;
	SDL_Surface *superficieInstrucao;
	SDL_Surface *superficieCreditos;
	SDL_Surface *superficieRanking;
	SDL_Surface *superficieSair;
	SDL_Surface *superficieNome;
	SDL_Surface *superficieSeta;
    SDL_Surface* superficieScore;
	SDL_Surface* superficieVolta;

    SDL_Rect r;

    SDL_Rect dstrect;
    SDL_Rect src; // 340/2 - metade da imagem para ficar centralizado
    SDL_Rect src1;
    SDL_Rect src2;
    SDL_Rect src3;
    SDL_Rect src4;
    SDL_Rect src5;
    SDL_Rect src6;
    SDL_Rect srcVolta;
    TTF_Font* fonteJogo;
    TTF_Font* fonteBotao;
    TTF_Font* fonteScore;
    TTF_Font* fonteRecord;
} Menu1;

Menu1* loadMenu1(SDL_Renderer* renderer);
void renderMenu1(SDL_Renderer* renderer,Menu1* menu);
int listenEventMenu1(Menu1* menu);
int loopMenu1(Menu1* menu);

#endif // DEBUG