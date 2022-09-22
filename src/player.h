#ifndef PLAYER
#define PLAYER

#include "common.h"
#include "map.h"
#include "textures.h"


typedef struct Player {


	int life;

	int isMoving;
    float moveSpeed;

    int facingSide;
    int frame;
    int moveMultiplier;

    CharacterTexture* characterTexture;


} Player;

Player* loadPlayerInitialState(CharacterTexture* texture);
void updateCharacterFrame(Player* player);


#endif //PLAYER