#ifndef PLAYER
#define PLAYER

#include "common.h"
#include "map.h"
#include "textures.h"


typedef struct Player {


	int life;

    BoardIndex boardIndex;

	int isMoving;
    float moveSpeed;

    int facingSide;
    int frame;
    int moveMultiplier;

    CharacterTexture* characterTexture;


} Player;

Player* loadPlayerInitialState(CharacterTexture* texture);


#endif //PLAYER