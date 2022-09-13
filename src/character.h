#ifndef CHARACTER
#define CHARACTER

#include "common.h"

#define CHARA_PATH "assets/chara.png"
#define CHARACTER_FRONT 0
#define CHARACTER_BACK 1
#define CHARACTER_LEFT 2
#define cHARACTER_RIGHT 3

typedef struct characterImage {

	SDL_Texture* characterSheet;
    SDL_Rect spritePosition[4][4];

    int spriteWidth;
    int spriteHeight;

    int frame;
    SDL_Rect displayRect;

} CharacterImage;

typedef struct characterStats {

	int life;

} CharacterStats;


typedef struct chara {

	CharacterImage characterImage;
	CharacterStats characterStats;

} Character;

Character* loadCharacter(SDL_Renderer* renderer);

#endif //CHARACTER