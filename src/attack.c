#include "attack.h"

AttackManager* loadAttackManager() {

    AttackManager* atkManager = (AttackManager*)malloc(sizeof(AttackManager));

    for(int i = 0; i < 5; i++) {

        atkManager->attackList[i] = NULL;
    }

    atkManager->nextAttackIndex = 0;

    return atkManager;
}

AttackTexture* loadAttackTexture(SDL_Renderer* renderer, const char* imgPath, int displayWidth, int displayHeight) {


    AttackTexture* atktexture = (AttackTexture*)malloc(sizeof(AttackTexture));

    atktexture->texture = IMG_LoadTexture(renderer, imgPath);
    atktexture->displayWidth = displayWidth;
    atktexture->displayHeight = displayHeight;

    return atktexture;

}


Attack* loadAttack(AttackTexture* texture, int atkSpeed, float atkInterval) {

    Attack* attack = (Attack*)malloc(sizeof(Attack));

    attack->atkTexture = texture;

    attack->atkSpeed = atkSpeed;
    attack->dstRect = fillRect(300, 300, texture->displayWidth, texture->displayHeight);

    return attack;

}