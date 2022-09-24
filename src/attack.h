#ifndef ATTACK
#define ATTACK

#include "common.h"
#include "textures.h"
#define FIRST_ATK_PATH "assets/energyball.png"

typedef struct attackTexture {

    SDL_Texture* texture;

} AttackTexture;

typedef struct attack {

    Timer timer;

    AttackTexture* atkTexture;

    float atkInterval;

    Vector attackPosition;
    Vector attackMovement;

    BoardIndex boardPosition;

    SDL_Rect dstRect;

} Attack;

typedef struct attackManager {

    Attack* attackList[5];

    int nextAttackIndex;

    AttackTexture* firstAttackTexture;
    AttackTexture* secondAttackTexture;

} AttackManager;

AttackManager* loadAttackManager();
AttackTexture* loadAttackTexture(SDL_Renderer* renderer, const char* imgPath);
Attack* loadAttack(AttackTexture* texture, Vector attackPosition, Vector attackMovement, BoardIndex attackBoardPosition);


#endif //ATTACK