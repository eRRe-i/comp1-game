#ifndef ATTACK
#define ATTACK

#include "common.h"
#include "textures.h"
#define FIRST_ATK_PATH "assets/energyball.png"

typedef struct attackTexture {

    SDL_Texture* texture;

    int displayWidth;
    int displayHeight;

} AttackTexture;

typedef struct attack {

    Timer timer;

    AttackTexture* atkTexture;

    int atkSpeed;
    float atkInterval;

    int x;
    int y;

    SDL_Rect dstRect;

} Attack;

typedef struct attackManager {

    Attack* attackList[5];

    int nextAttackIndex;

    AttackTexture* firstAttackTexture;
    AttackTexture* secondAttackTexture;

} AttackManager;

AttackManager* loadAttackManager();
AttackTexture* loadAttackTexture(SDL_Renderer* renderer, const char* imgPath, int displayWidth, int displayHeight);
Attack* loadAttack(AttackTexture* texture, int atkSpeed, float atkInterval);


#endif //ATTACK