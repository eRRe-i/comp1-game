#include "common.h"
#include "map.h"
#include "player.h"
#include "textures.h"


Player* loadPlayerInitialState(CharacterTexture* texture) {

	Player* player = (Player*)malloc(sizeof(Player));

	player->isMoving = FALSE;
	player->facingSide = CHARACTER_DOWN;
    player->frame = 0;

	BoardIndex previousBoardPosition;
	BoardIndex currentBoardPosition;

	player->characterTexture = texture;

	player->moveMultiplier = 1;
	player->moveSpeed = 2;
	player->life = 3;


	return player;

}




