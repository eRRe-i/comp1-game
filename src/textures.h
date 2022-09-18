#ifndef TEXTURES
#define TEXTURES

#define CHARA_PATH "assets/chara.png"
#define CHARACTER_DOWN 0
#define CHARACTER_UP 1
#define CHARACTER_LEFT 2
#define CHARACTER_RIGHT 3
#define CHARACTER_FRAME_RATE 200

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


MapTexture* loadMapTexture(SDL_Renderer* renderer);
CharacterTexture* loadCharacterTexture(SDL_Renderer* renderer);
SDL_Texture* loadImage(SDL_Renderer* renderer, const char* imgPath);


#endif //TEXTURES