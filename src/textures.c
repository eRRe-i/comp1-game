#include "textures.h"
#include <stdlib.h>

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

    characterTexture->frame = 0;
    characterTexture->isMoving = 1;

    characterTexture->displayRect.x=WINDOW_WIDTH/2 - 48/2;
    characterTexture->displayRect.y=WINDOW_HEIGHT/2 - 72/2;
    characterTexture->displayRect.w=48;
    characterTexture->displayRect.h=72;

    return characterTexture;
}

MapTexture* loadMapTexture(SDL_Renderer* renderer, const char* imgPath) {

	MapTexture* mapTexture = (MapTexture*)malloc(sizeof(MapTexture));

	mapTexture->mapTexture = loadImage(renderer, imgPath);
	
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

void moveCharacter(CharacterTexture* characterTexture) {

    if(characterTexture->isMoving)
        characterTexture->frame = (int)(SDL_GetTicks() / CHARACTER_FRAME_RATE)%4;
    else
        return;

}

void moveEnemy(EnemyTexture* enemyTexture) {

    if(enemyTexture->isMoving)
        enemyTexture->frame = (int)(SDL_GetTicks() / CHARACTER_FRAME_RATE)%4;
    else
        return;

}

/*
* TYPE = 1 -> BASIC_Enemy
* TYPE = 2 -> MEDIUM_Enemy
* TYPE = 3 -> HIGH_Enemy
*/
EnemyTexture* loadEnemyTexture(SDL_Renderer* renderer, int type) {

    EnemyTexture* enemyTexture = (EnemyTexture*)malloc(sizeof(EnemyTexture));

    if(type == 1){
        enemyTexture->EnemySheet = loadImage(renderer, BASIC_Enemy_PATH);
    }
    if(type == 2){
        enemyTexture->EnemySheet = loadImage(renderer, MEDIUM_Enemy_PATH);
    }
    if(type == 3){
        enemyTexture->EnemySheet = loadImage(renderer, HIGH_Enemy_PATH);
    }
    
    enemyTexture->spriteWidth = 472;
    enemyTexture->spriteHeight = 430;
    

    for(int i=0; i<2; i++) {
        for(int j=0; j<6; j++) {

            enemyTexture->spritePosition[i][j].x = enemyTexture->spriteWidth*j;
            enemyTexture->spritePosition[i][j].y = enemyTexture->spriteHeight*i;
            enemyTexture->spritePosition[i][j].w = enemyTexture->spriteWidth;
            enemyTexture->spritePosition[i][j].h = enemyTexture->spriteHeight;
        }
    }

    enemyTexture->frame = 0;
    enemyTexture->isMoving = 1;

    enemyTexture->displayRect.x= rand() % WINDOW_WIDTH + 20;
    enemyTexture->displayRect.y= rand() % WINDOW_HEIGHT + 20;
    enemyTexture->displayRect.w=48;
    enemyTexture->displayRect.h=41;

    return enemyTexture;
}