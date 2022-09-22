#ifndef TEXTURES
#define TEXTURES

#define CHARA_PATH "assets/chara.png"
#define BASIC_Enemy_PATH "assets/basic_monster.png"
#define MEDIUM_Enemy_PATH "assets/medium_monster.png"
#define HIGH_Enemy_PATH "assets/high_monster.png"
#define NO_KEYBOARD_INPUT -1
#define CHARACTER_DOWN 0
#define CHARACTER_UP 1
#define CHARACTER_LEFT 2
#define CHARACTER_RIGHT 3
#define CHARACTER_FRAME_RATE 200
#define BLOCKSIZE 32

#define MAP_PATH "assets/Map1.png"

#include "common.h"

typedef struct characterTexture {

	SDL_Texture* characterSheet;
    SDL_Rect spritePosition[4][4];

    int spriteWidth;
    int spriteHeight;

    SDL_Rect displayRect;

} CharacterTexture;


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

typedef struct enemyTexture {

	SDL_Texture* EnemySheet;
    SDL_Rect spritePosition[2][6];

    int spriteWidth;
    int spriteHeight;

    SDL_Rect displayRect;

} EnemyTexture;




MapTexture* loadMapTexture(SDL_Renderer* renderer, int id);
CharacterTexture* loadCharacterTexture(SDL_Renderer* renderer);
SDL_Texture* loadImage(SDL_Renderer* renderer, const char* imgPath);
SDL_Rect fillRect(int x, int y, int w, int h);
EnemyTexture* loadEnemyTexture(SDL_Renderer* renderer, int type);


#endif //TEXTURES