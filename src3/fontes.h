#ifndef FONTES
#define FONTES
#include <SDL2/SDL_ttf.h>

typedef struct fontes {

    TTF_Font* fonteJogo;
	TTF_Font* fonteScore;
	TTF_Font* fonteRecord;
	SDL_Color preto;
	SDL_Color branco;

} Fontes;

Fontes* loadFontesInitialState();

#endif //FONTES