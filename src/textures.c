#include "common.h"
#include "textures.h"

SDL_Texture* loadImage(SDL_Renderer* renderer, const char* imgPath) {

	SDL_Texture* texture = IMG_LoadTexture(renderer, imgPath);

	if(texture == NULL){

		printf("Erro no Carregamento da imagem %s\n", imgPath);
	} 

	return texture;

}

CharacterTexture* loadCharacterTexture(SDL_Renderer* renderer) {

    CharacterTexture* characterTexture = (CharacterTexture*)malloc(sizeof(CharacterTexture));

    characterTexture->characterSheet = loadImage(renderer, CHARA_PATH);

    characterTexture->spriteWidth = 400;
    characterTexture->spriteHeight = 600;
    

    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {

            characterTexture->spritePosition[i][j].x = characterTexture->spriteWidth*j;
            characterTexture->spritePosition[i][j].y = characterTexture->spriteHeight*i;
            characterTexture->spritePosition[i][j].w = characterTexture->spriteWidth;
            characterTexture->spritePosition[i][j].h = characterTexture->spriteHeight;
        }
    }


    characterTexture->displayRect.x=WINDOW_WIDTH/2 - 48/2;
    characterTexture->displayRect.y=WINDOW_HEIGHT/2 - 72/2;
    characterTexture->displayRect.w=48;
    characterTexture->displayRect.h=72;

    return characterTexture;
}

MapTexture* loadMapTexture(SDL_Renderer* renderer) {

	MapTexture* mapTexture = (MapTexture*)malloc(sizeof(MapTexture));

	mapTexture->mapTexture = loadImage(renderer, MAP_PATH);
	
	SDL_QueryTexture(mapTexture->mapTexture, NULL, NULL, &mapTexture->width, &mapTexture->height);

	mapTexture->displayRect.x = 0;
	mapTexture->displayRect.y = 0;
	mapTexture->displayRect.w = mapTexture->width;
	mapTexture->displayRect.h = mapTexture->height;

	return mapTexture;
}

SDL_Rect fillRect(int x, int y, int w, int h) {
    
    SDL_Rect rect = {.x = x, .y = y, .w = w, .h = h};

    return rect;
}

