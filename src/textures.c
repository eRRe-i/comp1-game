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
    characterTexture->displayRect.y=WINDOW_HEIGHT/2 - 72/2 + 20;
    characterTexture->displayRect.w=48;
    characterTexture->displayRect.h=72;

    return characterTexture;
}

MapTexture* loadMapTexture(SDL_Renderer* renderer, int id) {

    char imgPath[MAX_SIZE];
    sprintf(imgPath, "assets/Map%d.png",id);
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

/*
* TYPE = 1 -> BASIC_Enemy
* TYPE = 2 -> MEDIUM_Enemy
* TYPE = 3 -> HIGH_Enemy
*/
EnemyTexture* loadEnemyTexture(SDL_Renderer* renderer, int type) {

    EnemyTexture* enemyTexture = (EnemyTexture*)malloc(sizeof(EnemyTexture));

    switch (type){
        case 1:
        enemyTexture->Enemiesheet = loadImage(renderer, BASIC_Enemy_PATH);
        break;
        case 2:
        enemyTexture->Enemiesheet = loadImage(renderer, MEDIUM_Enemy_PATH);
        break;
        case 3:
        enemyTexture->Enemiesheet = loadImage(renderer, HIGH_Enemy_PATH);
        break;
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

    enemyTexture->displayRect.w=32;
    enemyTexture->displayRect.h=27;

    return enemyTexture;
}

LifeTexture* loadLifeTexture(SDL_Renderer* renderer, int i){
    LifeTexture* lifeTexture = (LifeTexture*)malloc(sizeof(LifeTexture));
   
    lifeTexture->spriteWidth  = 300;
    lifeTexture->spriteHeight = 0;
    i +=1;
    for(int j=0; j<2; j++) {
        lifeTexture->spritePosition[0][j].x = lifeTexture->spriteWidth*j;
        lifeTexture->spritePosition[0][j].y = lifeTexture->spriteHeight;
        lifeTexture->spritePosition[0][j].w = 300;
        lifeTexture->spritePosition[0][j].h = 300;
    }

    // lifeTexture->displayRect.x = 50 + (i*13);
    // lifeTexture->displayRect.y = 50;
    lifeTexture->displayRect.w = 25;
    lifeTexture->displayRect.h = 25;
    lifeTexture->x = 25 + (i*30);
    lifeTexture->y = 25;
    lifeTexture->frame = 0;

    lifeTexture->texture = loadImage(renderer, "assets/life.png");

    return lifeTexture;
}