#include "attack.h"

AttackManager* loadAttackManager() {

    AttackManager* atkManager = (AttackManager*)malloc(sizeof(AttackManager));

    for(int i = 0; i < 5; i++) {

        atkManager->attackList[i] = NULL;
    }

    atkManager->nextAttackIndex = 0;


    return atkManager;
}

AttackTexture* loadAttackTexture(SDL_Renderer* renderer, const char* imgPath) {


    AttackTexture* atkTexture = (AttackTexture*)malloc(sizeof(AttackTexture));

    atkTexture->texture = IMG_LoadTexture(renderer, imgPath);

    return atkTexture;

}

Attack* loadAttack(AttackTexture* texture, Vector attackPosition, Vector globalPosition, Vector attackMovement) {

    Attack* attack = (Attack*)malloc(sizeof(Attack));

    attack->atkTexture = texture;

    attack->attackPosition = attackPosition;
    attack->globalPosition = globalPosition;
    attack->attackMovement = attackMovement;

    return attack;

}