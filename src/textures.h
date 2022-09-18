#ifndef TEXTURES
#define TEXTURES

#define CHARA_PATH "assets/chara.png"
#define BASIC_Enemy_PATH "assets/basic_monster.png"
#define MEDIUM_Enemy_PATH "assets/medium_monster.png"
#define HIGH_Enemy_PATH "assets/high_monster.png"

#define CHARACTER_FRONT 0
#define CHARACTER_BACK 1
#define CHARACTER_LEFT 2
#define CHARACTER_RIGHT 3
#define CHARACTER_FRAME_RATE 200

#define MAP_PATH "assets/Map%d.png"
#define MAP_PATH2 "assets/Map2.png"
  
#include "common.h"

typedef struct characterTexture {

	SDL_Texture* characterSheet;
    SDL_Rect spritePosition[4][4];

    int spriteWidth;
    int spriteHeight;

    int frame;
    int isMoving;

    SDL_Rect displayRect;

} CharacterTexture;

typedef struct EnemyTexture {

	SDL_Texture* EnemySheet;
    SDL_Rect spritePosition[2][6];

    int spriteWidth;
    int spriteHeight;

    int frame;
    int isMoving;

    SDL_Rect displayRect;

} EnemyTexture;



typedef struct mapTexture {

    SDL_Texture* mapTexture;
	SDL_Rect displayRect;

	int width;
	int height;

} MapTexture;



typedef struct textureContext {

    CharacterTexture* characterTexture;
    MapTexture* mapTexture;


    SDL_Renderer* renderer;

} TextureContext;


MapTexture* loadMapTexture(SDL_Renderer* renderer, const char* imgPath);
CharacterTexture* loadCharacterTexture(SDL_Renderer* renderer);
EnemyTexture* loadEnemyTexture(SDL_Renderer* renderer, int type);
SDL_Texture* loadImage(SDL_Renderer* renderer, const char* imgPath);
void moveCharacter(CharacterTexture* characterTexture);
void moveEnemy(EnemyTexture* characterTexture);

#endif //TEXTURES